#include <windows.h>
#include <wrl.h>  // ComPtr ����� ���� ���

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <d2d1_3.h> //ID2D1Factory8,ID2D1DeviceContext7
#pragma comment(lib, "d2d1.lib")

#include <dxgi1_6.h> // IDXGIFactory7
#pragma comment(lib, "dxgi.lib")

#include <dwrite.h>
#pragma comment(lib,"dwrite.lib")

using namespace Microsoft::WRL;

// ���� ����
HWND g_hwnd = nullptr;
ComPtr<ID3D11Device> g_d3dDevice;
ComPtr<IDXGISwapChain1> g_dxgiSwapChain;
ComPtr<ID2D1DeviceContext7> g_d2dDeviceContext;
ComPtr<ID2D1Bitmap1> g_d2dBitmapTarget;

// For DrawText
ComPtr<ID2D1SolidColorBrush> g_blackBrush;		
ComPtr<IDWriteFactory> g_dWriteFactory;
ComPtr<IDWriteTextFormat> g_dWriteTextFormat;

UINT g_width = 800;
UINT g_height = 600;
bool g_resized = false;

void Initialize(HWND hwnd);
void Uninitialize();

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
	{
		if (wParam == SIZE_MINIMIZED)
			break; // �ּ�ȭ�� ����

		UINT width = LOWORD(lParam); // �� �ʺ�
		UINT height = HIWORD(lParam); // �� ����			
		if (g_width != width || g_height != height)
		{
			g_width = width;
			g_height = height;
			g_resized = true;
		}
	}
	break;
	case WM_EXITSIZEMOVE:
		if (g_resized)
		{
			Uninitialize();
			Initialize(hWnd);
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// �ʱ�ȭ
void Initialize(HWND hwnd)
{
	// D3D11 ����̽� ����
	D3D_FEATURE_LEVEL featureLevel;
	D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT, levels, 1,
		D3D11_SDK_VERSION, g_d3dDevice.GetAddressOf(), &featureLevel, nullptr);

	// D2D ���丮 �� ����̽�
	ComPtr<ID2D1Factory8> d2dFactory;
	D2D1_FACTORY_OPTIONS options = {};
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, d2dFactory.GetAddressOf());

	ComPtr<IDXGIDevice> dxgiDevice;
	g_d3dDevice.As(&dxgiDevice);
	ComPtr<ID2D1Device7> d2dDevice;
	d2dFactory->CreateDevice((dxgiDevice.Get()), d2dDevice.GetAddressOf());
	d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, g_d2dDeviceContext.GetAddressOf());

	ComPtr<IDXGIFactory7> dxgiFactory;
	CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));


	// SwapChain ����
	DXGI_SWAP_CHAIN_DESC1 scDesc = {};
	scDesc.Width = g_width;
	scDesc.Height = g_height;
	scDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scDesc.SampleDesc.Count = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = 2;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dxgiFactory->CreateSwapChainForHwnd(g_d3dDevice.Get(), hwnd, &scDesc, nullptr, nullptr, g_dxgiSwapChain.GetAddressOf());

	// ����۸� Ÿ������ ����
	ComPtr<IDXGISurface> backBuffer;
	g_dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
	D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(scDesc.Format, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);
	g_d2dDeviceContext->CreateBitmapFromDxgiSurface(backBuffer.Get(), &bmpProps, g_d2dBitmapTarget.GetAddressOf());
	g_d2dDeviceContext->SetTarget(g_d2dBitmapTarget.Get());


	// Brush
	g_d2dDeviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), g_blackBrush.GetAddressOf());
	
	// DirectWrite ���͸��� ����ϴ�.
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(g_dWriteFactory),
		reinterpret_cast<IUnknown**>(g_dWriteFactory.GetAddressOf()));

	// DirectWrite �ؽ�Ʈ ���� ��ü�� ����ϴ�.
	g_dWriteFactory->CreateTextFormat(
		L"Cooper", // FontName    ������-���������-�׸�-�۲�-Ŭ�� ���� �۲��̸� Ȯ�ΰ���
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		50.0f,   // Font Size
		L"", //locale
		&g_dWriteTextFormat
	);	

	// �ؽ�Ʈ�� ���� �� �������� �߾ӿ� ����ϴ�.
	g_dWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	g_dWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

void Uninitialize()
{
	g_d3dDevice = nullptr;
	g_dxgiSwapChain = nullptr;
	g_d2dDeviceContext = nullptr;
	g_d2dBitmapTarget = nullptr;
}

void Render()
{
	g_d2dDeviceContext->BeginDraw();
	g_d2dDeviceContext->Clear(D2D1::ColorF(D2D1::ColorF::DarkSlateBlue));

	D2D1_SIZE_F size = g_d2dDeviceContext->GetSize();

	WCHAR sc_helloWorld[] = L"Hello, World! abc";
	g_d2dDeviceContext->DrawText(
		sc_helloWorld,
		ARRAYSIZE(sc_helloWorld) - 1,
		g_dWriteTextFormat.Get(),
		D2D1::RectF(0, 0, size.width, size.height / 2),
		g_blackBrush.Get()
	);

	g_d2dDeviceContext->EndDraw();
	g_dxgiSwapChain->Present(1, 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"MyD2DWindowClass";
	RegisterClass(&wc);

	SIZE clientSize = { (LONG)g_width,(LONG)g_height };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	g_hwnd = CreateWindowEx(0, L"MyD2DWindowClass", L"D2D1 Draw Text Example",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top,
		nullptr, nullptr, hInstance, nullptr);
	ShowWindow(g_hwnd, nCmdShow);

	CoInitialize(nullptr);
	Initialize(g_hwnd);

	// �޽��� ����
	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			Render(); 
		}
	}

	Uninitialize();
	CoUninitialize();
	return 0;
}
