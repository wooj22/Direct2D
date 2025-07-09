#pragma once
#include "Component.h"
#include "ScriptSystem.h"
#include "GameObject.h"

/* [Script Conponent]
* GameObject�� ���� Component���� controll�ϴ� script ������Ʈ�̴�.
* ���� ������������ �� class�� ��ӹ��� script�� �ۼ��Ͽ�
* ��ɺ��� ��ũ��Ʈ�� �и��ϰ�, ��Ȱ�� �� �� �ִ�. ex) Movement.cs, Inventory.cs
* 
* 
*/

class Script : public Component
{
public:
    /* script component cycle */
	Script() { ScriptSystem::Get().Regist(this); }
	~Script() override { ScriptSystem::Get().Unregist(this); }

	void OnEnable() override {}        // ������Ʈ Ȱ��ȭ��
    virtual void Awake() {}            // 
    virtual void Start() {}            // 
    virtual void Update() {}           // ������ ����
    virtual void FixedUpdate() {}      // physice update (0.02f ����)
	void OnDestroy() override {}       // 

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



