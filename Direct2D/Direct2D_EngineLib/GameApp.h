#pragma once
#include "D2DRenderer.h"
#include "Singleton.h"
#include "Windows.h"
#include "string"
using namespace std;

class GameApp
{
private:
	// window
	HINSTANCE		hInstance;		// �������� ���α׷� �ν��Ͻ� �ڵ�
	HWND			hWnd;			// ������ �ڵ�
	int				width = 1024;
	int				height = 768;
	wstring			winClassName = L"woo";
	wstring			titleName = L"D2D Project";
	string			modulePath;
	string			workingPath;

public:
	bool isLoop = true;

	GameApp(int inputWidth = 1920, int inputHeight = 1080) :
		width(inputWidth), height(inputHeight), hInstance(nullptr), hWnd(nullptr) { };
	virtual ~GameApp() = default;

	virtual void Init();
	void Loop();
	virtual void UnInitialize();
	virtual void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

