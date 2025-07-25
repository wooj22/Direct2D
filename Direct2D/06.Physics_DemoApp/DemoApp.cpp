#include "DemoApp.h"
#include "../Direct2D_EngineLib/RectTransform.h"
#include "StartScene.h"
#include "PlayScene.h"
#include "CollisionTestScene.h"

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	// matrix init
	Transform::unityMatrix =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * Transform::unityMatrix *
		D2D1::Matrix3x2F::Translation(width / 2.0f, height / 2.0f);
	RectTransform::unityMatrix =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * D2D1::Matrix3x2F::Translation(width / 2.0f, height / 2.0f);

	// scene init
	sceneManager.CreateScene<StartScene>();
	sceneManager.CreateScene<PlayScene>();
	sceneManager.CreateScene<CollisionTestScene>();
	sceneManager.SetCurrentScene(START);
	sceneManager.Init();
}

/// Game Release
void DemoApp::UnInit()
{
	__super::UnInit();
}

/// 윈도우 프로시저 메시지 처리
void DemoApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	__super::MessageProc(hwnd, uMsg, wParam, lParam);

	// game에 활용할 message 처리
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	}
}