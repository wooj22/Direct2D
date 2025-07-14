#pragma once
#include <assert.h>
#include <windows.h>     // Win32 API
#include <wrl.h>         // ComPtr ����Ʈ ������
#include <d3d11.h>       // Direct3D
#include <d2d1_3.h>      // Direct2D
#include <dxgi1_6.h>     // DXGI
#include <wincodec.h>    // WIC 
#include <dwrite.h>	     // Write
#include "Singleton.h"
#include "IRenderer.h"
#include <vector>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib,"windowscodecs.lib")
#pragma comment(lib,"dwrite.lib")
using namespace Microsoft::WRL;    // Microsoft::WRL::ComPtr<T>
using namespace std;

class RenderSystem : public Singleton<RenderSystem>
{
private:
	// renderList
	vector<IRenderer*> components;		// render ��ü��

	// window
	HWND hwnd;
	int width;
	int height;

public :
	// Direct2D Engine
	ComPtr<ID3D11Device> d3dDevice;				    // D3D Device (gpu ����)
	ComPtr<IDXGISwapChain1> swapChain;	            // SwapChain (������۸�)
	ComPtr<ID2D1DeviceContext7> renderTarget;       // D2D Device Context (�׸���)
	ComPtr<ID2D1Bitmap1> backBufferBitmap;	  	    // ȭ�� ��¿� D2D Bitmap (�׸� ���)
	ComPtr<IWICImagingFactory> wicImagingFactory;   // WIC Imaging Factory (�̹��� �ε�)		// TODO :: �����ص��� -> ���� ���ҽ��Ŵ������� ����
	ComPtr<IDWriteFactory> dWriteFactory;			// Text Write Factory (�ؽ�Ʈ �׸���)

	// componenet
	void Regist(IRenderer* component);
	void Unregist(IRenderer* component);

	// component system
	void Init(HWND hwnd, int width, int height);
	void Update();
	void Render();
	void UnInit();			


	// test
	void DrawRect(const D2D1_RECT_F& rect, const D2D1_COLOR_F& color, const D2D1_MATRIX_3X2_F& transform = D2D1::Matrix3x2F::Identity(), float strokeWidth = 1.0f)
	{
		// Brush ����
		ComPtr<ID2D1SolidColorBrush> brush;
		HRESULT hr = renderTarget->CreateSolidColorBrush(color, &brush);
		assert(SUCCEEDED(hr));

		// Transform ����
		renderTarget->SetTransform(transform);

		// �簢�� �׸���
		renderTarget->DrawRectangle(rect, brush.Get(), strokeWidth);

		// Transform �ʱ�ȭ
		renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}
};
