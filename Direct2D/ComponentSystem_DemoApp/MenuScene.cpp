#include "MenuScene.h"

void MenuScene::Start() 
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// menu scene game object
	cat = CreateObject<Cat>();
	fish = CreateObject<Fish>();

	// game object -> start
	__super::Start();

	// component�� �����ǰ� �� �� �θ� ����
	fish->transform->SetParent(cat->transform);
}

void MenuScene::Update() 
{
	// camera move
	if (InputManager::Get().GetKey(VK_LEFT)) camera->transform->AddPosition(-3, 0);
	if (InputManager::Get().GetKey(VK_RIGHT)) camera->transform->AddPosition(3, 0);
	if (InputManager::Get().GetKey(VK_UP)) camera->transform->AddPosition(0, 3);
	if (InputManager::Get().GetKey(VK_DOWN)) camera->transform->AddPosition(0, -3);

	// camera ����� update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// game object -> update
	__super::Update();
}

void MenuScene::Exit()
{
	// game object -> destroy
	__super::Exit();
}