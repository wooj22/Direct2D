#pragma once
#include "Component.h"
#include "ScriptSystem.h"

/* [Button Conponent]
* GameObject�� ���� Component���� controll�ϴ� script ������Ʈ�̴�.
* ���� ������������ �� class�� ��ӹ��� script�� �ۼ��Ͽ�
* ��ɺ��� ��ũ��Ʈ�� �и��ϰ�, ��Ȱ�� �� �� �ִ�. ex) Movement.cs, Inventory.cs
*/

class Script : public Component
{
public:
	// component cycle
	Script() { ScriptSystem::Get().Regist(this); }
	~Script() override { ScriptSystem::Get().Unregist(this); }

	void OnEnable() override {};
	virtual void Update() = 0;
	void OnDestroy() override {};
};



