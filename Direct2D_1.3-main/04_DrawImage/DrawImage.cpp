#include <windows.h>
#include <assert.h>
#include <wrl.h>  // ComPtr ����� ���� ���

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <d2d1_3.h> //ID2D1Factory8,ID2D1DeviceContext7
#pragma comment(lib, "d2d1.lib")

#include <dxgi1_6.h> // IDXGIFactory7
#pragma comment(lib, "dxgi.lib")

#include <wincodec.h>
#pragma comment(lib,"windowscodecs.lib")

using namespace Microsoft::WRL;

// ���� ����
HWND g_hwnd = nullptr;
ComPtr<ID3D11Device> g_d3dDevice;
ComPtr<IDXGISwapChain1> g_dxgiSwapChain;
ComPtr<ID2D1DeviceContext7> g_d2dDeviceContext;
ComPtr<ID2D1Bitmap1> g_d2dBitmapTarget;

// For ImageDraw
ComPtr<IWICImagingFactory> g_wicImagingFactory;
ComPtr<ID2D1Bitmap1> g_d2dBitmapFromFile;


UINT g_width = 1024;
UINT g_height = 768;
bool g_resized = false;

void Initialize(HWND hwnd);
void Uninitialize();

// WIC�� ���� PNG ���� �ε��Ͽ� ID2D1Bitmap1**���� ��ȯ
HRESULT CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1** outBitmap)
{
	ComPtr<IWICBitmapDecoder>     decoder;
	ComPtr<IWICBitmapFrameDecode> frame;
	ComPtr<IWICFormatConverter>   converter;

	// �� ���ڴ� ����
	HRESULT hr = g_wicImagingFactory->CreateDecoderFromFilename(
		path, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
	if (FAILED(hr)) return hr;

	// �� ù ������ ���
	hr = decoder->GetFrame(0, &frame);
	if (FAILED(hr)) return hr;

	// �� ���� ��ȯ�� ����
	hr = g_wicImagingFactory->CreateFormatConverter(&converter);
	if (FAILED(hr)) return hr;

	// �� GUID_WICPixelFormat32bppPBGRA�� ��ȯ
	hr = converter->Initialize(
		frame.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);
	if (FAILED(hr)) return hr;

	// �� Direct2D ��Ʈ�� �Ӽ� (premultiplied alpha, B8G8R8A8_UNORM)
	D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_NONE,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);

	// �� DeviceContext���� WIC ��Ʈ�����κ��� D2D1Bitmap1 ����
	hr = g_d2dDeviceContext->CreateBitmapFromWicBitmap(converter.Get(), &bmpProps, outBitmap);
	return hr;
}


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
	HRESULT hr;
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
		

	// Create WIC factory
	hr = CoCreateInstance(CLSID_WICImagingFactory,
			NULL,CLSCTX_INPROC_SERVER,
			__uuidof(g_wicImagingFactory),
			(void**)g_wicImagingFactory.GetAddressOf());

	hr = CreateBitmapFromFile(L"../Resource/mushroom.png", g_d2dBitmapFromFile.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void Uninitialize()
{
	//CoUninitialize(); ȣ������ Release�� ȣ��Ǿ�� ũ���ð� ���� ����.
	g_wicImagingFactory = nullptr;
	g_d2dBitmapFromFile = nullptr;

	g_d3dDevice = nullptr;
	g_dxgiSwapChain = nullptr;
	g_d2dDeviceContext = nullptr;
	g_d2dBitmapTarget = nullptr;
}

void Render()
{
	g_d2dDeviceContext->BeginDraw();
	g_d2dDeviceContext->Clear(D2D1::ColorF(D2D1::ColorF::DarkSlateBlue));

	D2D1_SIZE_F size;

	g_d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity()); // ��ȯ �ʱ�ȭ

	//1. 0,0 ��ġ�� ��Ʈ�� ��ü���� �׸���. (��ȯ�� �ʱ�ȭ)
	g_d2dDeviceContext->DrawBitmap(g_d2dBitmapFromFile.Get());

	//2. DestPos(ȭ�� ��ġ) ������ SrcPos(��Ʈ�� ��ġ)�� �׸���
	D2D1_VECTOR_2F DestPos{ 0,0 }, SrcPos{ 0,0 }; // ȭ�� ��ġ, ��Ʈ�� ��ġ
	size = { 0,0 };	//	�׸� ũ��
	D2D1_RECT_F DestRect{ 0,0,0,0 }, SrcRect{ 0,0,0,0 }; // ȭ�� ����, ��Ʈ�� ����
	D2D1_MATRIX_3X2_F transform;	// ��ȯ ���

	size = g_d2dBitmapFromFile->GetSize();
	DestPos = { 100,0 };
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width  ,DestPos.y + size.height  };
	g_d2dDeviceContext->DrawBitmap(g_d2dBitmapFromFile.Get(), DestRect);


	//3. DestRect(�׸� ����) ������ SrcRect(��Ʈ�� �Ϻ� ����)�� �׸���
	size = { 200,200 };
	DestPos = { 100,100 };
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width  ,DestPos.y + size.height };

	SrcPos = { 0,0 };
	SrcRect = { SrcPos.x,SrcPos.y, SrcPos.x + size.width,SrcPos.y + size.height};
	g_d2dDeviceContext->DrawBitmap(g_d2dBitmapFromFile.Get(), DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);


	//4. ��ȯ�� ����� �������� DestRect(�׸� ����) ������ SrcRect(��Ʈ�� �Ϻ� ����)�� �׸���
	DestPos = { 700,100 };
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width ,DestPos.y + size.height};

	transform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f,  // x�� ����
		D2D1::Point2F(DestPos.x, DestPos.y));        // ������
	g_d2dDeviceContext->SetTransform(transform);
	g_d2dDeviceContext->DrawBitmap(g_d2dBitmapFromFile.Get(), DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);

	//5. ���պ�ȯ�� ����� �������� DestRect(�׸� ����) ������ SrcRect(��Ʈ�� �Ϻ� ����)�� �׸���
	DestPos = { 0,0 };   // �׸� ��ġ�� 0,0���� �ϰ� �̵���ȯ�� ����Ѵ�.
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width,DestPos.y + size.height};

	transform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0.0f, 0.0f)) *
		D2D1::Matrix3x2F::Rotation(90.0f, D2D1::Point2F(0.0f, 0.0f)) * // 90�� ȸ��
		D2D1::Matrix3x2F::Translation(900.0f, 900.0f);  // �̵�

	// ������
	g_d2dDeviceContext->SetTransform(transform);
	g_d2dDeviceContext->DrawBitmap(g_d2dBitmapFromFile.Get(), DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);

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

	g_hwnd = CreateWindowEx(0, L"MyD2DWindowClass", L"D2D1 Clear Example",
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
