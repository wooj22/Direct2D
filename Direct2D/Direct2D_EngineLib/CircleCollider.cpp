#include "CircleCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Script.h"
#include "RenderSystem.h"
#include "BoxCollider.h"
#include "Rigidbody.h"

void CircleCollider::OnEnable()
{
    transform = owner->GetComponent<Transform>();
}

void CircleCollider::OnDestroy()
{

}

// UpdateBounds()
// circle collider�� aabb bound�� update�Ѵ�
// colldierSystem�� sap �˰��� ���ȴ�. (����ȭ)
void CircleCollider::UpdateBounds()
{
    Vector2 pos = transform->GetPosition() + offset;
    float scaledRadius = radius * transform->GetScale().x;

    minX = pos.x - scaledRadius;
    maxX = pos.x + scaledRadius;
    minY = pos.y - scaledRadius;
    maxY = pos.y + scaledRadius;
}

// isCollision()
// �Ѱܹ��� �ݶ��̴��� Ÿ�Կ� ���� �浹 ����� return�Ѵ�
// �浹�� ��� contact info�� ����Ѵ�
bool CircleCollider::isCollision(ICollider* other, ContactInfo& contact)
{
    if (!transform) return false;

    if (other->colliderType == ColliderType::Circle)
    {
        return CheckCircleCollision(static_cast<CircleCollider*>(other), contact);
    }
    else if (other->colliderType == ColliderType::Box)
    {
        return CheckBoxCollision(static_cast<BoxCollider*>(other), contact);
    }

    return false;
}

// CheckCircleCollision()
// this circle�� other circle�� �浹 üũ
bool CircleCollider::CheckCircleCollision(CircleCollider* other, ContactInfo& contact)
{
    Vector2 posA = transform->GetPosition() + offset;
    Vector2 posB = other->transform->GetPosition() + other->offset;

    Vector2 scaleA = transform->GetScale();
    Vector2 scaleB = other->transform->GetScale();

    float scaledRadiusA = radius * scaleA.x;
    float scaledRadiusB = other->radius * scaleB.x;

    Vector2 diff = posA - posB;
    float distSq = diff.SqrMagnitude();
    float radiusSum = scaledRadiusA + scaledRadiusB;

    if (distSq > radiusSum * radiusSum)
        return false;

    // Contact Info
    Vector2 dir;
    if (distSq == 0.0f)
        dir = Vector2(1, 0); // ����ó�� (������ ������ ��)
    else
        dir = diff.Normalized();

    contact.normal = dir;
    contact.point = posB + dir * scaledRadiusB;

    return true;
}

// CheckBoxCollision()
// this circle�� other box�� �浹 üũ
bool CircleCollider::CheckBoxCollision(BoxCollider* other, ContactInfo& contact)
{
    Vector2 circlePos = transform->GetPosition() + offset;
    Vector2 circleScale = transform->GetScale();
    float radiusScaled = radius * circleScale.x;

    Vector2 boxPos = other->transform->GetPosition() + other->offset;
    Vector2 boxScale = other->transform->GetScale();
    Vector2 boxSizeScaled = other->size * boxScale;
    Vector2 halfBoxSize = boxSizeScaled * 0.5f;

    // Clamp point ���
    float closestX = clamp(circlePos.x, boxPos.x - halfBoxSize.x, boxPos.x + halfBoxSize.x);
    float closestY = clamp(circlePos.y, boxPos.y - halfBoxSize.y, boxPos.y + halfBoxSize.y);

    Vector2 closestPoint(closestX, closestY);
    Vector2 diff = circlePos - closestPoint;

    float distSq = diff.SqrMagnitude();

    if (distSq > radiusScaled * radiusScaled)
        return false;

    // Contact Info
    contact.point = closestPoint;

    if (distSq == 0.0f)
    {
        // �߽��� �ڽ� ���ο� ������ �� ���, ����ó��
        contact.normal = Vector2(0, 1);
    }
    else
    {
        contact.normal = diff.Normalized();
    }

    return true;
}

// FinalizeCollision()
// ���� ������ �浹 ������ ���� ������ �浹 ������ ���Ͽ�
// isTrigger ������ ���� Enter, Stay, Exit �浹 �̺�Ʈ �Լ��� ȣ���Ѵ�.
void CircleCollider::FinalizeCollision()
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

void CircleCollider::OnCollisionEnter(ICollider* other, ContactInfo& contact)
{
    Vector2 pos = transform->GetPosition();
    Vector2 prePos = transform->prePosition;

    // �ະ ����
    if (contact.normal.x != 0) { pos.x = prePos.x; }
    if (contact.normal.y != 0)
    {
        pos.y = prePos.y;

        // isGrounded
        if (contact.normal.y > 0)
        {
            Rigidbody* rb = owner->GetComponent<Rigidbody>();
            if (rb)
            {
                rb->groundContactCount++;
                rb->isGrounded = true;
            }
        }
    }
    transform->SetPosition(pos);

    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

void CircleCollider::OnCollisionStay(ICollider* other, ContactInfo& contact)
{
    Vector2 pos = transform->GetPosition();
    Vector2 prePos = transform->prePosition;

    // �ະ ����
    if (contact.normal.x != 0) { pos.x = prePos.x; }
    if (contact.normal.y != 0) { pos.y = prePos.y; }
    transform->SetPosition(pos);

    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionStay(other);
}

void CircleCollider::OnCollisionExit(ICollider* other, ContactInfo& contact)
{
    // isGrounded
    Rigidbody* rb = owner->GetComponent<Rigidbody>();
    if (rb && contact.normal.y > 0)
    {
        rb->groundContactCount--;

        if (rb->groundContactCount <= 0)
        {
            rb->groundContactCount = 0;
            rb->isGrounded = false;
        }
    }

    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionExit(other);
}

void CircleCollider::OnTriggerEnter(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerEnter(other);
}

void CircleCollider::OnTriggerStay(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerStay(other);
}

void CircleCollider::OnTriggerExit(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerExit(other);
}

bool CircleCollider::Raycast(const Ray& ray, float maxDistance, RaycastHit& hitInfo)
{
    // TODO 
    return false;
}

void CircleCollider::DebugColliderDraw()
{
    Vector2 localPos = Vector2(offset.x, -offset.y);

    D2D1_ELLIPSE ellipse = D2D1::Ellipse(
        D2D1::Point2F(localPos.x, localPos.y),
        radius,
        radius
    );

    RenderSystem::Get().DebugDrawCircle(ellipse, transform->GetScreenMatrix());
}