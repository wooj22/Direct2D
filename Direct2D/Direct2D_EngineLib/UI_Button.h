#pragma once
#include "GameObject.h"
#include "RectTransform.h"
#include "ImageRenderer.h"
#include "ScreenTextRenderer.h"
#include "Button.h"

/* [UI_Button GameObject]
* ���� Button�� �ʿ��� ����� �߰��ص� �⺻ Button GameObject
*/

class UI_Button : public GameObject
{
public:
	RectTransform* rectTransform;
	ImageRenderer* imageRenderer;
	ScreenTextRenderer* screenTextRenderer;
	Button* button;

	UI_Button() { OutputDebugStringA("UI_Button()\n"); }
	~UI_Button() override { OutputDebugStringA("~UI_Button()\n"); }

	void Awake() override;
	void Start() override {}
	void Update() override {}
	void Destroyed() override {}
};

