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
// ���� ������Ʈ�� ��� ������Ʈ ���� ��
void ScriptSystem::Awake()
{
	for (Script* script : components)
	{
		script->Awake();
	}
}

// Awake()����, ù Update ����
void ScriptSystem::Start()
{
	for (Script* script : components)
	{
		script->Start();
		script->started = true;
	}
}

// update -> ������(deltaTime) ���� ȣ��
void ScriptSystem::Update()
{
	for (Script* script : components)
	{
		// update�� ������ ���
		if (!script->started)
		{
			script->Awake(); 
			script->Start();
		}
		script->Update();
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