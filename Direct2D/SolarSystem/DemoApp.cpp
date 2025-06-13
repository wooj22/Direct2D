#include "DemoApp.h"

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	// camera
	mainCamera.SetSize(width, height);

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
	sun.transform.SetPosition(50, 0);
	earth.transform.SetPosition(200, 0);
	moon.transform.SetPosition(50, 0);
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();

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