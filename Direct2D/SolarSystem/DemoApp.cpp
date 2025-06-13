#include "DemoApp.h"

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Sun.png", 
		sunImage.image.GetAddressOf());

	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Earth.png",
		earthImage.image.GetAddressOf());

	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Moon.png",
		moonImage.image.GetAddressOf());
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
	sunImage.UnInit();
	earthImage.UnInit();
	moonImage.UnInit();

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