#pragma once
#include "../Direct2D_EngineLib/GameApp.h"
#include "../Direct2D_EngineLib/Camera.h"

class DemoApp : public GameApp
{
public:
	enum SceneName { MENU, PLAY };	// scene enum
	static Camera_Old* mainCamera;		// ��ü scene�� ���� �� ī�޶�
	
	DemoApp(int inputWidth, int inputHeight) : GameApp(inputWidth, inputHeight) {};
	~DemoApp() override = default;

	void Init() override;
	void UnInit() override;
	void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};