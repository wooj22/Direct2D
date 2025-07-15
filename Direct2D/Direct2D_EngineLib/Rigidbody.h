#pragma once
#include "Component.h"
#include "PhysicsSystem.h"
#include "Vector2.h"

/* [Rigidbody Component]
* 
*/

class Transform;
class Rigidbody : public Component
{
private:
    Transform* transform = nullptr;

public:
    Vector2 velocity = Vector2::zero;           // �ӵ�
    Vector2 acceleration = Vector2::zero;       // ���ӵ�
    float mass = 1.0f;                          // ����
    bool useGravity = true;                     // �߷� ��� ����
    float gravityScale = 50.0f;                 // �߷� ������
    float drag = 0.0f;                          // ���� ����, ������ (Ŭ���� �ӵ� ����)

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
};


