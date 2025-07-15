#pragma once
#include "ICollider.h"
#include "ColliderSystem.h"

/* [BoxCollider Component]
* �ڽ� ������ �浹 ������ �����Ͽ� �浹 üũ�� ����ϴ� ������Ʈ
* transform�� position�� �������� offset��ŭ ����߸� size�� �ݶ��̴� ������ ������.
* bound ������ Update�ϸ� ICollider�� ��ӹ��� ��� ������ �ݶ��̴����� ��ȣ�ۿ��� �����Ѵ�.
* isTrigger �÷��׸� �����Ͽ� Block, Overlap ó���� ������ �� �ִ�.
* ColliderSystem�� ��ϵǾ� �浹 �߻��� �浹 �̺�Ʈ�� ȣ���ϰ� �ǰ�,
* �� �̺�Ʈ ������ �°� Script ������Ʈ�� ã�� �̺�Ʈ �Լ��� ȣ�����ش�. -> ����Ƽó�� ��� �����ϵ���
* Block(collistion mode)�ÿ��� transform�� ���� ������ position���� �ǵ��ư��� �Ѵ�.
* 
* TODO :: �ະ �̵� ���� ���� �߰�
* ����� �߷� ���� ��带 ����Ͽ� �浹�߿��� yPos�� �������̰� ���Ƶΰ� �ִµ�
* �̷��� �ϸ� �߷��� �ȹ޴� �ֵ鵵 �¿쿡 �ִ� �ݶ��̴��� �浹���� �� ���Ʒ��� �������� (ž��)
* �߷°� ���� ���� �浹 �߿��� �� �׵θ������� ���������� ������ �� �ְ� �ϰ����
* �ݶ��̴� �����θ� ���̻� ���ư��� ���ϰ�, ������ ����� �ݴ�Ǵ� �������δ� �̵��� �� �ְԲ�
* 
* => �浹 �߿��� �ݶ��̴��� ��鿡 �°� �̲������� �ϰ�, �ݶ��̴� �����δ� �� �� ���� ����, 
     �ٸ� �������δ� ������ �� �ֵ��� �ϰ� �ʹ�.
     ����Ƽó�� �ݶ��̴��� ��Ÿ�����͸� �߰��ؼ� �浹�� ���� �븻�� ���� �� �ֵ��� �� ����
*/

class Transform;
class CircleCollider;
class BoxCollider : public ICollider
{
public:
    Transform* transform = nullptr;

    // collider
    Vector2 offset = Vector2::zero;
    Vector2 size = { 10,10 };
    
public:
    // component cycle
    BoxCollider() 
    { 
        colliderType = ColliderType::Box;
        ColliderSystem::Get().Regist(this);
    }
    ~BoxCollider() override { ColliderSystem::Get().Unregist(this); }

    void OnEnable() override;
    void UpdateBounds() override;
    bool isCollision(ICollider* other) override;
    void FinalizeCollision() override;
    void OnDestroy() override;

private:
    // collision event
    void OnCollisionEnter(ICollider* other) override;
    void OnCollisionStay(ICollider* other) override;
    void OnCollisionExit(ICollider* other) override;
    void OnTriggerEnter(ICollider* other) override;
    void OnTriggerStay(ICollider* other) override;
    void OnTriggerExit(ICollider* other) override;

    // collision cheak
    bool CheckAABBCollision(BoxCollider* other);
    bool CheakCircleCollision(CircleCollider* other);

    // ���� üũ�� (�ະ �̵� ������ ����)
    bool InternalCheckCollision(ICollider* other);

public:
    // debug draw
    void DebugColliderDraw() override;
};


