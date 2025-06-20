#include "PlayScene.h"

void PlayScene::Start()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// menu scene game object
	

	// game object -> start
	__super::Start();

	// component�� �����ǰ� �� �� �θ� ����
	
}

void PlayScene::Update()
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

void PlayScene::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}