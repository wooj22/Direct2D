#include "DemoApp.h"

/// Game Init
void DemoApp::Init() 
{
	__super::Init();
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();
}

/// Game Render
void DemoApp::Render() 
{
	d2dRenderer.d2dDeviceContext->BeginDraw();
	d2dRenderer.d2dDeviceContext->Clear(D2D1::ColorF(D2D1::ColorF::YellowGreen));
	d2dRenderer.d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());

	// �̹��� ũ�� ���
	D2D1_SIZE_F bitmapSize = d2dRenderer.d2dBitmapFromFile->GetSize();

	// ���� ���� Ÿ��(â)�� ũ�� ���
	D2D1_SIZE_F renderTargetSize = d2dRenderer.d2dDeviceContext->GetSize();

	// �߾� ��ġ ���
	float destX = (renderTargetSize.width - bitmapSize.width) / 2.0f;
	float destY = (renderTargetSize.height - bitmapSize.height) / 2.0f;

	// �߾ӿ� ����� DestRect ����
	D2D1_RECT_F destRect = {
		destX,
		destY,
		destX + bitmapSize.width,
		destY + bitmapSize.height
	};

	// �̹��� ��� (���߾ӿ�)
	d2dRenderer.d2dDeviceContext->DrawBitmap(d2dRenderer.d2dBitmapFromFile.Get(), destRect);

	d2dRenderer.d2dDeviceContext->EndDraw();
	d2dRenderer.dxgiSwapChain->Present(1, 0);
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