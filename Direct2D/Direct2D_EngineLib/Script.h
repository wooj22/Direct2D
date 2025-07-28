#pragma once
#include "Component.h"
#include "ScriptSystem.h"
#include "GameObject.h"
#include "ICollider.h"

/* [Script Conponent]
* GameObject�� ���� Component���� controll�ϴ� script ������Ʈ�̴�.
* ���� ������������ �� class�� ��ӹ��� script�� �ۼ��Ͽ�
* ��ɺ��� ��ũ��Ʈ�� �и��ϰ�, ��Ȱ�� �� �� �ִ�. ex) Movement.cs, Inventory.cs
* -> ����Ƽ�� �������̾��� �����ϸ� �ȴ�.
*/

class ICollider;
class Script : public Component
{
public:
    bool started = false;

    /* script component cycle */
	Script() { ScriptSystem::Get().Regist(this); }
	~Script() override { ScriptSystem::Get().Unregist(this); }

	void OnEnable() override {}        // ������Ʈ Ȱ��ȭ��
    virtual void Awake() {}            // Update()���� 1ȸ ȣ��
    virtual void Start() {}            // Awake() ���� Updtae() ���� ���� 1ȸ ȣ��
    virtual void Update() {}           // ������ ���� �ݺ� ȣ��
    virtual void FixedUpdate() {}      // ���� ������Ʈ 0.02f ���� �ݺ� ȣ��
	void OnDestroy() override {}       // ������Ʈ or ������Ʈ �Ҹ� ����

    /* Collition Event */
    // trigger
    virtual void OnTriggerEnter(ICollider* other) {}
    virtual void OnTriggerStay(ICollider* other) {}
    virtual void OnTriggerExit(ICollider* other) {}

    // collision
    virtual void OnCollisionEnter(ICollider* other, const ContactInfo& contact) {}
    virtual void OnCollisionStay(ICollider* other, const ContactInfo& contact) {}
    virtual void OnCollisionExit(ICollider* other, const ContactInfo& contact) {}

    /* Instantiate */
};



