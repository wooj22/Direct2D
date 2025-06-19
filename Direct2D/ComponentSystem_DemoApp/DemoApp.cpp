#include "DemoApp.h"

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	// camera
	mainCamera = new Camera(width, height);
	mainCamera->transform = mainCamera->AddComponent<Transform>();
	//mainCamera->SetSize(width, height);

	// matrix init
	Transform::SetCameraMatrix(mainCamera->transform->GetWorldMatrix());
	Transform::unityMatrix = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * Transform::unityMatrix *
		D2D1::Matrix3x2F::Translation(width / 2.0f, height / 2.0f);

	// game object init
	cat = new Cat;
	cat->transform = cat->AddComponent<Transform>();
	cat->sr = cat->AddComponent<SpriteRenderer>();
	cat->sr->SetImage(L"../Resource/Cat.png");
	cat->transform->SetPosition(10, 10);
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();

	// camera move
	if (InputManager::Get().GetKey(VK_LEFT)) mainCamera->transform->AddPosition(-3, 0);
	if (InputManager::Get().GetKey(VK_RIGHT)) mainCamera->transform->AddPosition(3, 0);
	if (InputManager::Get().GetKey(VK_UP)) mainCamera->transform->AddPosition(0, 3);
	if (InputManager::Get().GetKey(VK_DOWN)) mainCamera->transform->AddPosition(0, -3);

	// camera ����� update
	Transform::SetCameraMatrix(mainCamera->transform->GetWorldMatrix());

	// debug
	/*OutputDebugStringA("����� ������ : ");
	string str1 = to_string(cat->transform->GetPosition().x) +
		", " + to_string(cat->transform->GetPosition().y);
	OutputDebugStringA(str1.c_str());
	OutputDebugStringA("\n");

	OutputDebugStringA("ī�޶� ������ : ");
	string str2 = to_string(mainCamera->transform->GetPosition().x) +
		", " + to_string(mainCamera->transform->GetPosition().y);
	OutputDebugStringA(str2.c_str());
	OutputDebugStringA("\n");*/
}

/// Game Release
void DemoApp::UnInit()
{
	__super::UnInit();
}

/// ������ ���ν��� �޽��� ó��
void DemoApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	__super::MessageProc(hwnd, uMsg, wParam, lParam);

	// game�� Ȱ���� message ó��
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	}
}