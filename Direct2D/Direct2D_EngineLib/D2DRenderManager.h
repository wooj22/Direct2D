#pragma once
#include <assert.h>
#include <windows.h>     // Win32 API
#include <wrl.h>         // ComPtr ����Ʈ ������
#include <d3d11.h>       // Direct3D
#include <d2d1_3.h>      // Direct2D
#include <dxgi1_6.h>     // DXGI
#include <wincodec.h>    // WIC 
#include "Singleton.h"
#include "IRenderer.h"
#include <vector>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib,"windowscodecs.lib")
using namespace Microsoft::WRL;    // Microsoft::WRL::ComPtr<T>
using namespace std;

class D2DRenderManager : public Singleton<D2DRenderManager>
{
private:
	// renderList
	vector<IRenderer*> renderList;

	// window
	HWND hwnd;
	int width;
	int height;

public :
	// Direct2D Engine
	ComPtr<ID3D11Device> d3dDevice;				 // D3D Device (gpu ����)
	ComPtr<IDXGISwapChain1> swapChain;	         // SwapChain (������۸�)
	ComPtr<ID2D1DeviceContext7> deviceContext;   // D2D Device Context (�׸���)
	ComPtr<ID2D1Bitmap1> renderTarget;	  	     // ȭ�� ��¿� D2D Bitmap render Target (�׸� ���)
	ComPtr<IWICImagingFactory> wicImagingFactory;   // WIC Imaging Factory (�̹��� �ε�)

	// game flow
	void Init(HWND hwnd, int width, int height);
	void Render();
	void UnInit();			

	// functions
	HRESULT CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1** outBitmap);	// �̹��� �ε�
};
