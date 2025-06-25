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

	UI_Text() {}
	~UI_Text() override {}

	void Awake() override;
	void Start() override {}
	void Update() override {}
	void Destroy() override {}
};
