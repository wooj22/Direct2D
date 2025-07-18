#include "DemoApp.h"
#include "../Direct2D_EngineLib/RectTransform.h"
#include "Scene1.h"
#include "Scene2.h"

// static member init
Camera_Old* DemoApp::mainCamera = nullptr;

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	// main camera init
	mainCamera = new Camera_Old(width, height);
	mainCamera->transform = mainCamera->AddComponent<Transform>();

	// matrix init
	Transform::SetCameraMatrix(mainCamera->transform->GetWorldMatrix());
	Transform::unityMatrix =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * Transform::unityMatrix *
		D2D1::Matrix3x2F::Translation(width / 2.0f, height / 2.0f);

	RectTransform::unityMatrix =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * D2D1::Matrix3x2F::Translation(width / 2.0f, height / 2.0f);

	// scene init
	sceneManager.CreateScene<Scene1>();
	sceneManager.CreateScene<Scene2>();

	sceneManager.SetCurrentScene(SCENE1);
	sceneManager.Init();
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