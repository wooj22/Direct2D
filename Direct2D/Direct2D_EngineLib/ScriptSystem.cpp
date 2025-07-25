#include "ScriptSystem.h"
#include "Script.h"

// component 등록
void ScriptSystem::Regist(Script* component)
{
	components.push_back(component);
}

// component 등록 해제
void ScriptSystem::Unregist(Script* component)
{
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == component) {
			components.erase(it);
			return;
		}
	}
}

// update -> 프레임(deltaTime) 단위 호출
void ScriptSystem::Update()
{
	for (Script* script : components)
	{
		// update중 생성된 경우
		if (!script->started)
		{
			script->Awake(); 
			script->Start();
			script->started = true;
		}
		script->Update();
	}
}

// fixed udpate -> deltaTime에 따라 늦어졌다면 여러번 호출하고 넘어감
void ScriptSystem::FixedUpdate()
{
	for (auto* component : components)
	{
		if (component) component->FixedUpdate();
	}
}