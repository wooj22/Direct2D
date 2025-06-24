#include "TransformSystem.h"
#include "Transform.h"

// component ���
void TransformSystem::Regist(ITransform* component)
{
	components.push_back(component);
}

// component ��� ����
void TransformSystem::Unregist(ITransform* component)
{
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == component) {
			components.erase(it);
			return;
		}
	}
}

// component system
void TransformSystem::Update() 
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}
}