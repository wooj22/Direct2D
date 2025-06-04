#pragma once
#include "D2DRenderer.h"
#include "Singleton.h"
#include "Windows.h"
#include "string"
using namespace std;

class GameApp
{
protected:
	// window
	HINSTANCE		hInstance;		// �������� ���α׷� �ν��Ͻ� �ڵ�
	HWND			hWnd;			// ������ �ڵ�
	int				width = 1920;
	int				height = 1080;
	wstring			winClassName = L"woo";
	wstring			titleName = L"Direct 2D Project";
	string			modulePath;
	string			workingPath;

	void Render();

public:
	bool isLoop = true;

	GameApp(int inputWidth = 1920, int inputHeight = 1080) :
		width(inputWidth), height(inputHeight), hInstance(nullptr), hWnd(nullptr) { };
	virtual ~GameApp() = default;

	virtual void Init();
	void Loop();
	virtual void UnInit();
	virtual void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

