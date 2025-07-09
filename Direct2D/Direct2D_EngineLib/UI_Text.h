#pragma once
#include "GameObject.h"
#include "RectTransform.h"
#include "ScreenTextRenderer.h"

/* [UI_Text GameObject]
* ���� ScreenText�� �ʿ��� ����� �߰��ص� �⺻ UI_Text GameObject
*/

class UI_Text : public GameObject
{
public:
	RectTransform* rectTransform;
	ScreenTextRenderer* screenTextRenderer;

	UI_Text() 
	{ 
		rectTransform = AddComponent<RectTransform>();
		screenTextRenderer = AddComponent <ScreenTextRenderer>();
		OutputDebugStringA("UI_Text()\n"); 
	}
	~UI_Text() override { OutputDebugStringA("~UI_Text()\n"); }

	void Awake() override {}
	void SceneStart() override {}
	void Update() override {}
	void Destroyed() override {}
};
