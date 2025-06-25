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
void ScriptSystem::Update()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}
}