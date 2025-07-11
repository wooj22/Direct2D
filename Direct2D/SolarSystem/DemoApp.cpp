#include "DemoApp.h"

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	// camera
	mainCamera.SetSize(width, height);

	// matrix init
	Transform::SetCameraMatrix(mainCamera.transform.GetWorldMatrix());
	Transform::unityMatrix = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * Transform::unityMatrix *
		D2D1::Matrix3x2F::Translation(width/2.0f, height/2.0f);

	// image load
	renderSystem.CreateBitmapFromFile(L"../Resource/Sun.png", sun.sprite.GetAddressOf());
	renderSystem.CreateBitmapFromFile(L"../Resource/Earth.png", earth.sprite.GetAddressOf());
	renderSystem.CreateBitmapFromFile(L"../Resource/Moon.png", moon.sprite.GetAddressOf());

	// 부모 지정
	earth.transform.SetParent(&sun.transform);
	moon.transform.SetParent(&earth.transform);

	// 초기화
	earth.transform.SetPosition(300, 0);
	moon.transform.SetPosition(50, 0);
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();

	// camera move
	if (Input::Get().GetKey(VK_LEFT)) mainCamera.transform.AddPosition(-3,0);
	if (Input::Get().GetKey(VK_RIGHT)) mainCamera.transform.AddPosition(3, 0);
	if (Input::Get().GetKey(VK_UP)) mainCamera.transform.AddPosition(0, 3);
	if (Input::Get().GetKey(VK_DOWN)) mainCamera.transform.AddPosition(0, -3);

	// camera 역행렬 update
	Transform::SetCameraMatrix(mainCamera.transform.GetWorldMatrix());

	// image transform update
	sun.transform.AddRotation(-0.5f);
	earth.transform.AddRotation(-0.2f);
	moon.transform.AddRotation(-1);
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