#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Script.h"
#include "RenderSystem.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include <string>

void BoxCollider::OnEnable_Inner()
{
    ColliderSystem::Get().Regist(this);
	transform = this->gameObject->transform;
}

void BoxCollider::OnDisable_Inner()
{
	ColliderSystem::Get().Unregist(this);
}

void BoxCollider::OnDestroy_Inner()
{
    ColliderSystem::Get().Unregist(this);
}

// UpdateBounds()
// box collider의 aabb bound를 update한다
void BoxCollider::UpdateBounds()
{
    Vector2 center = GetCenter();
    Vector2 scale = transform->GetWorldScale();
    Vector2 halfSize = Vector2(size.x * 0.5f * scale.x, size.y * 0.5f * scale.y);

    minX = center.x - halfSize.x;
    maxX = center.x + halfSize.x;
    minY = center.y - halfSize.y;
    maxY = center.y + halfSize.y;
}

// isCollision()
// 넘겨받은 콜라이더의 타입에 따른 충돌 결과를 return한다
// 충돌한 경우 contact info를 계산한다
bool BoxCollider::isCollision(ICollider* other, ContactInfo& contact)
{
    if (!transform) return false;

    if (other->colliderType == ColliderType::Box)
    {
        return CheckAABBCollision(static_cast<BoxCollider*>(other), contact);
    }
    else if (other->colliderType == ColliderType::Circle)
    {
        return CheckCircleCollision(static_cast<CircleCollider*>(other), contact);
    }

    return false;
}

// FinalizeCollision()
// 이전 프레임 충돌 정보와 현재 프레임 충돌 정보를 비교하여
// isTrigger 유무에 따라 Enter, Stay, Exit 충돌 이벤트 함수를 호출한다.
void BoxCollider::FinalizeCollision()
{
    // Enter & Stay
    for (auto& pair : currentFrameCollisions)
    {
        ICollider* other = pair.first;
        ContactInfo& contact = pair.second;

        if (lastFrameCollisions.find(other) == lastFrameCollisions.end())
        {
            if (isTrigger || other->isTrigger)
                OnTriggerEnter(other);
            else
                OnCollisionEnter(other, contact);
        }
        else
        {
            if (isTrigger || other->isTrigger)
                OnTriggerStay(other);
            else
                OnCollisionStay(other, contact);
        }
    }

    // Exit
    for (auto& pair : lastFrameCollisions)
    {
        ICollider* other = pair.first;
        ContactInfo& contact = pair.second;

        if (currentFrameCollisions.find(other) == currentFrameCollisions.end())
        {
            if (isTrigger || other->isTrigger)
                OnTriggerExit(other);
            else
                OnCollisionExit(other, contact);
        }
    }

    lastFrameCollisions = currentFrameCollisions;
    currentFrameCollisions.clear();
}

// CheckAABBCollision()
// this box와 other box의 aabb 충돌 결과 반환
bool BoxCollider::CheckAABBCollision(BoxCollider* other, ContactInfo& contact)
{
    // 1. AABB
    if (maxX < other->minX || minX > other->maxX || maxY < other->minY || minY > other->maxY)
        return false;

    // 2. 충돌 지점: 두 AABB 중심 중간점
    Vector2 thisCenter = GetCenter();
    Vector2 otherCenter = other->GetCenter();
    contact.point = (thisCenter + otherCenter) * 0.5f;

    // 3. 축별 침투 깊이 계산
    float overlapX = min(maxX, other->maxX) -max(minX, other->minX);
    float overlapY = min(maxY, other->maxY) - max(minY, other->minY);

    // 4. 침투가 적은 축을 따라 법선 결정
    if (overlapX < overlapY)
    {
        // X축 방향 법선
        contact.normal = (thisCenter.x < otherCenter.x) ? Vector2(-1, 0) : Vector2(1, 0);
        contact.depth = overlapX;
    }
    else
    {
        // Y축 방향 법선
        contact.normal = (thisCenter.y > otherCenter.y) ? Vector2(0, 1) : Vector2(0, -1);
        contact.depth = overlapY;
    }

    return true;
}

// CheckCircleCollision()
// this box와 other circle의 충돌 결과 반환
bool BoxCollider::CheckCircleCollision(CircleCollider* other, ContactInfo& contact)
{
    Vector2 boxCenter = GetCenter();
    Vector2 boxSize = transform->GetWorldScale() * size * 0.5f;

    Vector2 circleCenter = other->GetCenter();
    float circleRadius = other->radius * other->transform->GetWorldScale().x;

    // AABB 내부에서 가장 가까운 점 찾기
    float closestX = clamp(circleCenter.x, boxCenter.x - boxSize.x, boxCenter.x + boxSize.x);
    float closestY = clamp(circleCenter.y, boxCenter.y - boxSize.y, boxCenter.y + boxSize.y);
    Vector2 closestPoint(closestX, closestY);

    // 원 중심과 가장 가까운 점 사이 거리
    Vector2 diff = circleCenter - closestPoint;
    float distSq = diff.SqrMagnitude();

    if (distSq > circleRadius * circleRadius)
        return false;

    // Contact Info
    contact.point = closestPoint;

    if (distSq == 0.0f)
    {
        contact.normal = Vector2(0, 1); // 예외 처리 : 안쪽 완전히 포함
        contact.depth = circleRadius;
    }
    else
    {
        float distance = sqrtf(distSq);
        contact.normal = -diff.Normalized();
        contact.depth = circleRadius - distance;
    }

    return true;
}

// Raycast()
// 광선과 this collider의 충돌 결과 반환
bool BoxCollider::Raycast(const Ray& ray, float maxDistance, RaycastHit& hitInfo)
{
    // 레이 방향이 0일 수 있으므로 예외 처리
    float dirX = ray.direction.x;
    float dirY = ray.direction.y;

    float tMinX, tMaxX;
    if (dirX != 0.0f)
    {
        tMinX = (minX - ray.origin.x) / dirX;
        tMaxX = (maxX - ray.origin.x) / dirX;
        if (tMinX > tMaxX) std::swap(tMinX, tMaxX);
    }
    else
    {
        // 레이가 X축으로 평행한 경우, 바운드를 벗어나면 충돌 없음
        if (ray.origin.x < minX || ray.origin.x > maxX)
            return false;
        tMinX = -INFINITY;
        tMaxX = INFINITY;
    }

    float tMinY, tMaxY;
    if (dirY != 0.0f)
    {
        tMinY = (minY - ray.origin.y) / dirY;
        tMaxY = (maxY - ray.origin.y) / dirY;
        if (tMinY > tMaxY) std::swap(tMinY, tMaxY);
    }
    else
    {
        if (ray.origin.y < minY || ray.origin.y > maxY)
            return false;
        tMinY = -INFINITY;
        tMaxY = INFINITY;
    }

    float tEnter = max(tMinX, tMinY);
    float tExit = min(tMaxX, tMaxY);

    if (tExit < 0 || tEnter > tExit || tEnter > maxDistance)
        return false;

    // 충돌 정보 기록
    hitInfo.distance = tEnter;
    hitInfo.point = ray.origin + ray.direction * tEnter;
    hitInfo.collider = this;

    return true;
}

void BoxCollider::OnCollisionEnter(ICollider* other, ContactInfo& contact)
{
    Rigidbody* rb = gameObject->GetComponent<Rigidbody>();
    if (rb)
    {
        // ground
        rb->CorrectPosition(contact);
        if (contact.normal.y > 0)
        {
            rb->groundContactCount++;
            rb->isGrounded = true;
        }

        // script
        auto scripts = gameObject->GetComponents<Script>();
        for (auto s : scripts)
            s->OnCollisionEnter(other, contact);
    }
}

void BoxCollider::OnCollisionStay(ICollider* other, ContactInfo& contact)
{
    Rigidbody* rb = gameObject->GetComponent<Rigidbody>();
    if (rb)
    {
        // ground
        if (contact.normal.y > 0)
        {
            rb->isGrounded = true;
        }

        // script
        auto scripts = gameObject->GetComponents<Script>();
        for (auto s : scripts)
            s->OnCollisionStay(other, contact);
    }
}

void BoxCollider::OnCollisionExit(ICollider* other, ContactInfo& contact)
{
    // isGrounded
    Rigidbody* rb = gameObject->GetComponent<Rigidbody>();
    if (rb)
    {
        // ground
        if (contact.normal.y > 0)
        {
            rb->groundContactCount--;

            if (rb->groundContactCount <= 0)
            {
                rb->groundContactCount = 0;
                rb->isGrounded = false;
            }
        }
        
        // block free
        if (contact.normal.x > 0)      rb->isBlockedLeft = false;
        else if (contact.normal.x < 0) rb->isBlockedRight = false;
        if (contact.normal.y > 0)      rb->isBlockedDown = false;
        else if (contact.normal.y < 0) rb->isBlockedUp = false;

        // script
        auto scripts = gameObject->GetComponents<Script>();
        for (auto s : scripts)
            s->OnCollisionExit(other, contact);
    } 
}

void BoxCollider::OnTriggerEnter(ICollider* other)
{
    // script
    auto scripts = gameObject->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerEnter(other);
}

void BoxCollider::OnTriggerStay(ICollider* other)
{
    // script
    auto scripts = gameObject->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerStay(other);
}

void BoxCollider::OnTriggerExit(ICollider* other)
{
    // script
    auto scripts = gameObject->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerExit(other);
}

Vector2 BoxCollider::GetCenter() const
{
    // transform 위치 + offset + size의 절반 (중심)
    Vector2 scale = transform->GetWorldScale();
    Vector2 worldPos = transform->GetWorldPosition();
    return worldPos + Vector2(offset.x * scale.x, offset.y * scale.y);
}

void BoxCollider::DebugColliderDraw()
{
    // rect
    float left = -size.x * 0.5f + offset.x;
    float right = size.x * 0.5f + offset.x;
    float top = -size.y * 0.5f - offset.y;
    float bottom = size.y * 0.5f - offset.y;

    D2D1_RECT_F localRect = D2D1::RectF(left, top, right, bottom);
    RenderSystem::Get().DebugDrawRect(localRect, transform->GetScreenMatrix());

    // center
    D2D1_ELLIPSE ellipse2 = D2D1::Ellipse(
        D2D1::Point2F(offset.x, -offset.y),
        2,
        2
    );
    RenderSystem::Get().DebugDrawCircle(ellipse2, transform->GetScreenMatrix());
}