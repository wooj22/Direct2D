#include "DemoApp.h"

/// Game Init
void DemoApp::Init() {
	__super::Init();
}

/// Game Release
void DemoApp::UnInitialize() {
	__super::UnInitialize();
}

/// ������ ���ν��� �޽��� ó��
void DemoApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	__super::MessageProc(hwnd, uMsg, wParam, lParam);

	// game�� Ȱ���� message ó��
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	}
}