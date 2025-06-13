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
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Sun.png", sun.image.GetAddressOf());
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Earth.png", earth.image.GetAddressOf());
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Moon.png", moon.image.GetAddressOf());

	// �� ����
	sun.AxisCoreection();
	earth.AxisCoreection();
	moon.AxisCoreection();

	// �θ� ����
	earth.transform.SetParent(&sun.transform);
	moon.transform.SetParent(&earth.transform);

	// �ʱ�ȭ
	earth.transform.SetPosition(300, 0);
	moon.transform.SetPosition(50, 0);
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();

	// camera move
	if (InputManager::Get().GetKey(VK_LEFT)) mainCamera.transform.AddPosition(-3,0);
	if (InputManager::Get().GetKey(VK_RIGHT)) mainCamera.transform.AddPosition(3, 0);
	if (InputManager::Get().GetKey(VK_UP)) mainCamera.transform.AddPosition(0, 3);
	if (InputManager::Get().GetKey(VK_DOWN)) mainCamera.transform.AddPosition(0, -3);

	// camera ����� update
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