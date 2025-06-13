#include "DemoApp.h"

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	// image load
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Sun.png", sunImage.image.GetAddressOf());
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Earth.png", earthImage.image.GetAddressOf());
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Moon.png", moonImage.image.GetAddressOf());

	// �� ����
	sunImage.AxisCoreection();
	earthImage.AxisCoreection();
	moonImage.AxisCoreection();

	// �θ� ����
	earthImage.transform.SetParent(&sunImage.transform);
	moonImage.transform.SetParent(&earthImage.transform);

	// ��ġ �ʱ�ȭ
	earthImage.transform.SetPosition(200, 0);
	moonImage.transform.SetPosition(50, 0);
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();

	// image transform update
	
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