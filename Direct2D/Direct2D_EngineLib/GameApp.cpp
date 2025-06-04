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
	d2dRenderer.Init(hWnd, width, height); // direct 2D init
}

/// Update
void GameApp::Update()
{
	
}

/// Render
void GameApp::Render()
{
	d2dRenderer.g_d2dDeviceContext->BeginDraw();		// �׸��� ����
	d2dRenderer.g_d2dDeviceContext->Clear(D2D1::ColorF(D2D1::ColorF::DarkSlateBlue));		// ����

	D2D1_SIZE_F size;
	d2dRenderer.g_d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity()); // Render ��ġ �⺻ sest

	//1. 0,0 ��ġ�� ��Ʈ�� ��ü���� �׸���. (��ȯ�� �ʱ�ȭ)
	d2dRenderer.g_d2dDeviceContext->DrawBitmap(d2dRenderer.g_d2dBitmapFromFile.Get());

	//2. DestPos(ȭ�� ��ġ) ������ SrcPos(��Ʈ�� ��ġ)�� �׸���
	D2D1_VECTOR_2F DestPos{ 0,0 }, SrcPos{ 0,0 }; // ȭ�� ��ġ, ��Ʈ�� ��ġ
	size = { 0,0 };	//	�׸� ũ��
	D2D1_RECT_F DestRect{ 0,0,0,0 }, SrcRect{ 0,0,0,0 }; // ȭ�� ����, ��Ʈ�� ����
	D2D1_MATRIX_3X2_F transform;	// ��ȯ ���

	// ȭ�� ��ġ�� �����ϰ�, ��Ʈ�� ũ�� ��ŭ DestRect�� �����Ͽ� ��Ʈ�� �׸���
	DestPos = { 100,0 };
	size = d2dRenderer.g_d2dBitmapFromFile->GetSize();
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };
	d2dRenderer.g_d2dDeviceContext->DrawBitmap(d2dRenderer.g_d2dBitmapFromFile.Get(), DestRect);

	//3. DestRect(�׸� ����) ������ SrcRect(��Ʈ�� �Ϻ� ����)�� �׸���
	size = { 200,200 };
	DestPos = { 100,100 };
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };

	SrcPos = { 0,0 }; // ��Ʈ���� �Ϻ� ������ �׸��� ���� SrcPos ����
	SrcRect = { SrcPos.x,SrcPos.y, SrcPos.x + size.width - 1 ,SrcPos.y + size.height - 1 };
	d2dRenderer.g_d2dDeviceContext->
		DrawBitmap(d2dRenderer.g_d2dBitmapFromFile.Get(),
			DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);

	//4. ��ȯ�� ����� �������� DestRect(�׸� ����) ������ SrcRect(��Ʈ�� �Ϻ� ����)�� �׸���
	DestPos = { 700,100 };
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };

	transform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f,  // x�� ����
		D2D1::Point2F(DestPos.x, DestPos.y));         // ������
	d2dRenderer.g_d2dDeviceContext->SetTransform(transform);
	d2dRenderer.g_d2dDeviceContext->
		DrawBitmap(d2dRenderer.g_d2dBitmapFromFile.Get(),
			DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);

	//5. ���պ�ȯ�� ����� �������� DestRect(�׸� ����) ������ SrcRect(��Ʈ�� �Ϻ� ����)�� �׸���
	DestPos = { 0,0 };   // �׸� ��ġ�� 0,0���� �ϰ� �̵���ȯ�� ����Ѵ�.
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };

	transform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0.0f, 0.0f)) *
		D2D1::Matrix3x2F::Rotation(90.0f, D2D1::Point2F(0.0f, 0.0f)) * // 90�� ȸ��
		D2D1::Matrix3x2F::Translation(900.0f, 900.0f);  // �̵�

	// ������
	d2dRenderer.g_d2dDeviceContext->SetTransform(transform);
	d2dRenderer.g_d2dDeviceContext->
		DrawBitmap(d2dRenderer.g_d2dBitmapFromFile.Get(),
			DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);

	d2dRenderer.g_d2dDeviceContext->EndDraw();
	d2dRenderer.g_dxgiSwapChain->Present(1, 0);
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
	CoUninitialize();		// com ��ü ����
}
