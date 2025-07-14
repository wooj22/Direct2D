#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Script.h"
#include "RenderSystem.h"
#include "DebugGizmo.h"

void BoxCollider::OnEnable()
{
    transform = this->owner->GetComponent<Transform>();
}

bool BoxCollider::isCollision(ICollider* other)
{
    if (other->colliderType == ColliderType::Box)
    {
        return CheckAABB(static_cast<BoxCollider*>(other));
    }
    else if (other->colliderType == ColliderType::Circle)
    {
        // TODO :: circle collider
    }

    return false;
}

void BoxCollider::OnDestroy()
{
    
}

void BoxCollider::OnCollisionEnter(ICollider* other)
{
    // ���� ��ġ�� �̵�

    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);

    OutputDebugStringA("Test OnCollisionEnter!");
}

void BoxCollider::OnTriggerEnter(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerEnter(other);

    OutputDebugStringA("Test OnTriggerEnter!");
}

bool BoxCollider::CheckAABB(BoxCollider* other)
{
    // this�� ���� ��ġ ��� (offset.y ���� ����)
    Vector2 posA = transform->GetPosition() + Vector2(offset.x, -offset.y);
    Vector2 scaleA = transform->GetScale();  // Vector2 Ÿ���̶�� ����

    // �������� �ݿ��� �� ũ��
    Vector2 halfSizeA = (size * scaleA) * 0.5f;

    // other�� ���� ��ġ ��� (offset.y ���� ����)
    Vector2 posB = other->transform->GetPosition() + Vector2(other->offset.x, -other->offset.y);
    Vector2 scaleB = other->transform->GetScale();

    // �������� �ݿ��� �� ũ��
    Vector2 halfSizeB = (other->size * scaleB) * 0.5f;

    // AABB �浹 �˻�
    bool collisionX = fabs(posA.x - posB.x) <= (halfSizeA.x + halfSizeB.x);
    bool collisionY = fabs(posA.y - posB.y) <= (halfSizeA.y + halfSizeB.y);

    return collisionX && collisionY;
}

void BoxCollider::DebugDraw()
{
    // �ݶ��̴� ���� ���� ���� rect (0,0 �߽�)
    float left = -size.x * 0.5f;
    float right = size.x * 0.5f;
    float top = -size.y * 0.5f;
    float bottom = size.y * 0.5f;
    D2D1_RECT_F localRect = D2D1::RectF(left, top, right, bottom);

    // offset�� matrix�� ���� �� y ����
    auto offsetMatrix = D2D1::Matrix3x2F::Translation(offset.x, -offset.y);

    // ��� �� ���� (transform ����, offset ����)
    auto finalMatrix = transform->GetScreenMatrix() * offsetMatrix;

    RenderSystem::Get().DrawRect(localRect, D2D1::ColorF(D2D1::ColorF::Lime), finalMatrix);
}

//void BoxCollider::DrawDebug()
//{
//    // �ݶ��̴� ���� ���� ���� rect (0,0 �߽�)
//    float left = -size.x * 0.5f;
//    float right = size.x * 0.5f;
//    float top = -size.y * 0.5f;
//    float bottom = size.y * 0.5f;
//    D2D1_RECT_F localRect = D2D1::RectF(left, top, right, bottom);
//
//    // offset�� matrix�� ���� �� y ����
//    auto offsetMatrix = D2D1::Matrix3x2F::Translation(offset.x, -offset.y);
//
//    // ��� �� ���� (transform ����, offset ����)
//    auto finalMatrix = transform->GetScreenMatrix() * offsetMatrix;
//
//    //DebugGizmo::Get().AddGizmoRect(finalMatrix, localRect);
//}