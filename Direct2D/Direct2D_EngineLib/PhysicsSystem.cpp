#include "PhysicsSystem.h"
#include "Rigidbody.h"

// component ���
void PhysicsSystem::Regist(Rigidbody* component)
{
	components.push_back(component);
}

// component ��� ����
void PhysicsSystem::Unregist(Rigidbody* component)
{
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == component) {
			components.erase(it);
			return;
		}
	}
}

// component system
void PhysicsSystem::Update()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}
}
