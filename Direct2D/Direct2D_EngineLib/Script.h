#pragma once
#include "Component.h"
#include "ScriptSystem.h"
#include "GameObject.h"

/* [Script Conponent]
* GameObject�� ���� Component���� controll�ϴ� script ������Ʈ�̴�.
* ���� ������������ �� class�� ��ӹ��� script�� �ۼ��Ͽ�
* ��ɺ��� ��ũ��Ʈ�� �и��ϰ�, ��Ȱ�� �� �� �ִ�. ex) Movement.cs, Inventory.cs
* 
* Awake(), Start() -> SceneManager���� ���� Awake(), Start() ���Ŀ� ȣ��
*                     started �÷��� üũ�� �ϱ� ������ udpate�߿��� ȣ�� ����  
* Update(), FixedUpdate() ->���� �������� ȣ���Ѵ�.
*/

class Script : public Component
{
public:
    bool started = false; // update�� �����Ǵ� ��츦 ���� flag

    /* script component cycle */
	Script() { ScriptSystem::Get().Regist(this); }
	~Script() override { ScriptSystem::Get().Unregist(this); }

	void OnEnable() override {}        // ������Ʈ Ȱ��ȭ��
    virtual void Awake() {}            // ������Ʈ�� ��� ������Ʈ�� ������ ���� ���� 1ȸ ȣ��
    virtual void Start() {}            // Awake() ���� ���� 1ȸ ȣ��
    virtual void Update() {}           // ������ ���� �ݺ� ȣ��
    virtual void FixedUpdate() {}      // ���� ������Ʈ 0.02f ���� �ݺ� ȣ��
	void OnDestroy() override {}       // ������Ʈ or ������Ʈ �Ҹ� ����

    /* Collition Event */
    // trigger
    virtual void OnTriggerEnter() {}
    virtual void OnTriggerStay() {}
    virtual void OnTriggerExit() {}

    // collision
    virtual void OnCollisionEnter() {}
    virtual void OnCollisionStay() {}
    virtual void OnCollisionExit() {}
};



