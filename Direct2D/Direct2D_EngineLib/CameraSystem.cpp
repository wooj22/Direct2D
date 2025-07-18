#include "CameraSystem.h"
#include "Camera.h"

/// Component ���
void CameraSystem::Regist(Camera* component)
{
	components.push_back(component);
}

/// Component ��� ����
void CameraSystem::Unregist(Camera* component)
{
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == component) {
			components.erase(it);
			return;
		}
	}
}

void CameraSystem::Update()
{
	for (Camera* cam : components)
	{
		cam->Update();
	}
}