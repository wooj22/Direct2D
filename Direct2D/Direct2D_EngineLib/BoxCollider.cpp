#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Script.h"
#include "RenderSystem.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include <string>

void BoxCollider::OnEnable()
{
    transform = this->owner->GetComponent<Transform>();
}

void BoxCollider::OnDestroy()
{

}

// UpdateBounds()
// box collider�� aabb bound�� update�Ѵ�
void BoxCollider::UpdateBounds()
{
    Vector2 scale = transform->GetScale();
    Vector2 scaledSize(size.x * scale.x, size.y * scale.y);
    Vector2 halfSize = scaledSize * 0.5f;
    Vector2 center = GetCenter();

    minX = center.x - halfSize.x;
    maxX = center.x + halfSize.x;
    minY = center.y - halfSize.y;
    maxY = center.y + halfSize.y;
}

// isCollision()
// �Ѱܹ��� �ݶ��̴��� Ÿ�Կ� ���� �浹 ����� return�Ѵ�
// �浹�� ��� contact info�� ����Ѵ�
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
// ���� ������ �浹 ������ ���� ������ �浹 ������ ���Ͽ�
// isTrigger ������ ���� Enter, Stay, Exit �浹 �̺�Ʈ �Լ��� ȣ���Ѵ�.
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
// this box�� other box�� aabb �浹 ��� ��ȯ
bool BoxCollider::CheckAABBCollision(BoxCollider* other, ContactInfo& contact)
{
    // 1. AABB
    if (maxX < other->minX || minX > other->maxX || maxY < other->minY || minY > other->maxY)
        return false;

    // 2. �浹 ����: �� AABB �߽� �߰���
    Vector2 thisCenter = GetCenter();
    Vector2 otherCenter = other->GetCenter();
    contact.point = (thisCenter + otherCenter) * 0.5f;

    // 3. �ະ ħ�� ���� ���
    float overlapX = min(maxX, other->maxX) -max(minX, other->minX);
    float overlapY = min(maxY, other->maxY) - max(minY, other->minY);

    // 4. ħ���� ���� ���� ���� ���� ����
    if (overlapX < overlapY)
    {
        // X�� ���� ����
        contact.normal = (thisCenter.x < otherCenter.x) ? Vector2(-1, 0) : Vector2(1, 0);
        contact.depth = overlapX;
    }
    else
    {
        // Y�� ���� ����
        contact.normal = (thisCenter.y > otherCenter.y) ? Vector2(0, 1) : Vector2(0, -1);
        contact.depth = overlapY;
    }

    return true;
}

// CheckCircleCollision()
// this box�� other circle�� �浹 ��� ��ȯ
bool BoxCollider::CheckCircleCollision(CircleCollider* other, ContactInfo& contact)
{
    Vector2 boxPos = transform->GetPosition() + offset;
    Vector2 boxScale = transform->GetScale();
    Vector2 boxSizeScaled(size.x * boxScale.x, size.y * boxScale.y);
    Vector2 halfBoxSize = boxSizeScaled * 0.5f;

    Vector2 circlePos = other->transform->GetPosition() + other->offset;
    Vector2 circleScale = other->transform->GetScale();
    float circleRadius = other->radius * circleScale.x;

    // AABB ���� ���� ����� ��(clamp)
    float closestX = clamp(circlePos.x, boxPos.x - halfBoxSize.x, boxPos.x + halfBoxSize.x);
    float closestY = clamp(circlePos.y, boxPos.y - halfBoxSize.y, boxPos.y + halfBoxSize.y);
    Vector2 closestPoint(closestX, closestY);

    // �� �߽ɰ� ���� ����� �� �Ÿ� ���� ���
    Vector2 diff = circlePos - closestPoint;
    float distSq = diff.SqrMagnitude();

    // �浹 ����
    if (distSq > circleRadius * circleRadius)
        return false;

    // �浹 ����
    contact.point = closestPoint;

    // �浹 ���� (�� �߽ɿ��� �ڽ� ����� ����)
    if (distSq == 0.0f)
    {
        // �߽��� �ڽ� �ȿ� ������ ���� �� (����ó��)
        // ���Ƿ� ���� ���� ����
        contact.normal = Vector2(0, 1);
        contact.depth = circleRadius;
    }
    else
    {
        float distance = sqrtf(distSq);
        contact.normal = diff / distance;
        contact.depth = circleRadius - distance;
    }

    return true;
}

// Raycast()
// ������ this collider�� �浹 ��� ��ȯ
bool BoxCollider::Raycast(const Ray& ray, float maxDistance, RaycastHit& hitInfo)
{
    // TODO 
    return false;
}

void BoxCollider::OnCollisionEnter(ICollider* other, ContactInfo& contact)
{
    Rigidbody* rb = owner->GetComponent<Rigidbody>();
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
        auto scripts = owner->GetComponents<Script>();
        for (auto s : scripts)
            s->OnCollisionEnter(other, contact);
    }
}

void BoxCollider::OnCollisionStay(ICollider* other, ContactInfo& contact)
{
    Rigidbody* rb = owner->GetComponent<Rigidbody>();
    if (rb)
    {
        // ground
        if (contact.normal.y > 0)
        {
            rb->isGrounded = true;
        }

        // script
        auto scripts = owner->GetComponents<Script>();
        for (auto s : scripts)
            s->OnCollisionStay(other, contact);
    }
}

void BoxCollider::OnCollisionExit(ICollider* other, ContactInfo& contact)
{
    // isGrounded
    Rigidbody* rb = owner->GetComponent<Rigidbody>();
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
        auto scripts = owner->GetComponents<Script>();
        for (auto s : scripts)
            s->OnCollisionExit(other, contact);
    } 
}

void BoxCollider::OnTriggerEnter(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerEnter(other);
}

void BoxCollider::OnTriggerStay(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerStay(other);
}

void BoxCollider::OnTriggerExit(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerExit(other);
}

Vector2 BoxCollider::GetCenter() const
{
    // transform ��ġ + offset + size�� ���� (�߽�)
    Vector2 scale = transform->GetScale();
    return transform->GetPosition() + Vector2(offset.x * scale.x, offset.y * scale.y);
}

void BoxCollider::DebugColliderDraw()
{
    float left = -size.x * 0.5f + offset.x;
    float right = size.x * 0.5f + offset.x;
    float top = -size.y * 0.5f - offset.y;
    float bottom = size.y * 0.5f - offset.y;

    D2D1_RECT_F localRect = D2D1::RectF(left, top, right, bottom);
    RenderSystem::Get().DebugDrawRect(localRect, transform->GetScreenMatrix());
}