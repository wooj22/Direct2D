#pragma once
#include "ICollider.h"
#include "ColliderSystem.h"

/* [CircleCollider Component]
* �� �浹 ������ �����Ͽ� �浹 üũ�� ����ϴ� ������Ʈ
* transform�� position�� �������� offset��ŭ ����߸� radius�� �� ������ ������
* bound ������ Update�ϸ� ColliderSystem���� sap �˰����� ����ϵ��� �����Ѵ�.
* ICollider�� ��ӹ��� ��� ������ �ݶ��̴����� ��ȣ�ۿ��� �����Ѵ�.
* isTrigger �÷��׸� �����Ͽ� Block, Overlap ó���� ������ �� �ִ�.
* Block(collistion mode)�ÿ��� transform�� ���� ������ position���� �ǵ��ư��� �Ѵ�.
* ColliderSystem�� ��ϵǾ� �浹 �߻��� �浹 �̺�Ʈ�� ȣ���ϰ� �ǰ�,
* �� �̺�Ʈ ������ �°� Script ������Ʈ�� ã�� �̺�Ʈ �Լ��� ȣ�����ش�. -> ����Ƽó�� ��� �����ϵ���
* 
* TODO :: �ະ �̵� ���� ���� �߰�
*/

class Transform;
class BoxCollider;
class CircleCollider : public ICollider
{
public:
    Transform* transform = nullptr;

    // collider
    Vector2 offset = Vector2::zero;
    float radius = 1.0f;

public:
    // component cycle
    CircleCollider() 
    {
        colliderType = ColliderType::Circle;
        ColliderSystem::Get().Regist(this);
    }
    ~CircleCollider() override { ColliderSystem::Get().Unregist(this); }

    void OnEnable() override;
    void UpdateBounds() override;
    bool isCollision(ICollider* other, ContactInfo& outContact) override;
    void FinalizeCollision() override;
    void OnDestroy() override;

private:
    // collistion cheak
    bool CheckCircleCollision(CircleCollider* other, ContactInfo& outContact);
    bool CheckBoxCollision(BoxCollider* other, ContactInfo& outContact);

    // ���� üũ�� (�ະ �̵� ������ ����)
    //bool InternalCheckCollision(ICollider* other);

private:
    // collision event
    void OnCollisionEnter(ICollider* other, ContactInfo& outContact) override;
    void OnCollisionStay(ICollider* other, ContactInfo& outContact) override;
    void OnCollisionExit(ICollider* other) override;
    void OnTriggerEnter(ICollider* other) override;
    void OnTriggerStay(ICollider* other) override;
    void OnTriggerExit(ICollider* other) override;

public:
    // debug draw
    void DebugColliderDraw() override;
};

