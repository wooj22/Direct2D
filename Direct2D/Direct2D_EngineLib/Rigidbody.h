#pragma once
#include "Component.h"
#include "PhysicsSystem.h"
#include "Vector2.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

/* [Rigidbody Component]
* ���� �Ի��� ����ϴ� ������Ʈ��, Transform�� �����Ͽ� �̵���Ų��.
* �ӵ�, ���ӵ�, ����, �߷�, ���� ���� ���� ���� �Ӽ��� �����ϸ�
* PhysicsSystem�� ��ϵǾ� FixedUpdate()�ֱ�� ������ ó���Ѵ�.
*/

class Transform;
class Rigidbody : public Component
{
private:
    Transform* transform = nullptr;

public:
    bool isGrounded;             // �ٴ� flag (collision)
    bool blockX, blockY;         // collision ���⿡ ���� �̵� ����

public:
    Vector2 velocity = Vector2::zero;           // �ӵ�
    Vector2 acceleration = Vector2::zero;       // ���ӵ�
    float mass = 1.0f;                          // ����
    bool useGravity = true;                     // �߷� ��� ����
    float gravityScale = 1.0f;                  // �߷� ������
    float drag = 0.0f;                          // ���� ����, ������ (Ŭ���� �ӵ� ����)

private:
    Vector2 impulse = Vector2::zero;            // ������ (�������� ��)

public:
    // component cycle
    Rigidbody()
    {
        PhysicsSystem::Get().Regist(this);
    }
    ~Rigidbody() override
    {
        PhysicsSystem::Get().Unregist(this);
    }

    void OnEnable() override;
    void FixedUpdate();
    void OnDestroy() override;

public:
    // func
    void AddForce(const Vector2& force);
    void AddImpulse(const Vector2& impulse);

    // friend
    friend class BoxCollider;
    friend class CircleCollider;
};


