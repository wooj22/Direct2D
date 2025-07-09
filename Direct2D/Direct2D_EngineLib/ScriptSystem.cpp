#include "ScriptSystem.h"
#include "Script.h"

// component ���
void ScriptSystem::Regist(Script* component)
{
	components.push_back(component);
}

// component ��� ����
void ScriptSystem::Unregist(Script* component)
{
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == component) {
			components.erase(it);
			return;
		}
	}
}

// component system
// update -> ������(deltaTime) ���� ȣ��
void ScriptSystem::Update()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}
}

// fixed udpate -> deltaTime�� ���� �ʾ����ٸ� ������ ȣ���ϰ� �Ѿ
void ScriptSystem::FixedUpdate()
{
	for (auto* component : components)
	{
		if (component) component->FixedUpdate();
	}
}