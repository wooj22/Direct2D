#include "GameApp.h"
#include "Singleton.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GameApp* pThis = nullptr;

	// ������ ������
	if (uMsg == WM_NCCREATE)
	{
		// lParam�Ű��������� this ����
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		pThis = reinterpret_cast<GameApp*>(cs->lpCreateParams);

		// ������ �ڵ��� GWLP_USERDATA(����� ������ ����)�� this ����
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
	}
	else {
		pThis = reinterpret_cast<GameApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (pThis)
		pThis->MessageProc(hwnd, uMsg, wParam, lParam);		// ��ü�� ��� �Լ� ȣ��

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/// �޽��� ó��
void GameApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	// ���� ���������� override
}


/// Init
void GameApp::Init()
{
	// module path save
	char szPath[MAX_PATH] = { 0, };
	GetModuleFileNameA(NULL, szPath, MAX_PATH);
	modulePath = szPath;
	OutputDebugStringA(string(string(modulePath) + string("\n")).c_str());

	// directory path save
	GetCurrentDirectoryA(MAX_PATH, szPath);
	workingPath = szPath;
	OutputDebugStringA(string(string(workingPath) + string("\n")).c_str());

	// get program handle
	hInstance = GetModuleHandle(NULL);

	// window class ����
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.lpszClassName = winClassName.c_str();
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	RegisterClassEx(&wc);

	SIZE clientSize = { width, height };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	// window â ����  -> WM_NCCREATE �޽��� �߻�
	hWnd = CreateWindowEx(
		0,
		winClassName.c_str(),
		titleName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top,
		NULL,
		NULL,
		hInstance,
		this  // this�� WindowProc�� ���� CREATESTRUCT ����ü Ÿ���� lParamdp �� ����ȴ�
	);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	CoInitialize(nullptr);					// com ��ü �ʱ�ȭ	
	d2dRenderer.Init(hWnd, width, height);  // direct 2D init
}

/// Update
void GameApp::Update()
{
	
}

/// Render
void GameApp::Render()
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

/// GameLoop
void GameApp::Loop()
{
	MSG msg = {};
	while (isLoop)
	{
		// message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				isLoop = false;
				break;
			}
				
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
		}

		Update();
		Render();
	}
}

/// Release
void GameApp::UnInit()
{
	d2dRenderer.UnInit();
	CoUninitialize();		// com ��ü ����
}
