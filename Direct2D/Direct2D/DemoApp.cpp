#include "DemoApp.h"

/// Game Init
void DemoApp::Init() 
{
	__super::Init();
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Cat.png", catImage.GetAddressOf());
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();
}

/// Game Render
void DemoApp::Render() 
{
	d2dRenderManager.renderTarget->BeginDraw();
	d2dRenderManager.renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::YellowGreen));
	d2dRenderManager.renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	// �̹��� ũ�� ���
	D2D1_SIZE_F bitmapSize = catImage->GetSize();

	// ���� ���� Ÿ��(â)�� ũ�� ���
	D2D1_SIZE_F renderTargetSize = d2dRenderManager.renderTarget->GetSize();

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
	d2dRenderManager.renderTarget->DrawBitmap(catImage.Get(), destRect);
	d2dRenderManager.renderTarget->EndDraw();

	// ����ü��
	d2dRenderManager.swapChain->Present(1, 0);
}

/// Game Release
void DemoApp::UnInit() 
{
	catImage = nullptr;
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