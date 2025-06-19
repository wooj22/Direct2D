#include "TransformSystem.h"
#include "Transform.h"

// component ���
void TransformSystem::Regist(Transform* component) 
{
	components.push_back(component);
}

// component ��� ����
void TransformSystem::Unregist(Transform* component) 
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
		(*it)->MakeLocalMatrix();
		(*it)->MakeWorldMatrix();
	}
}