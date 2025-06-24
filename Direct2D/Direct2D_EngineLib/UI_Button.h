#pragma once
#include "GameObject.h"
#include "RectTransform.h"
#include "ImageRenderer.h"
#include "Button.h"

/* [Button GameObject]
* Button�� �ʿ��� ����� �߰��ص� �⺻ Button GameObject
* ���� ���������� Button�� �� Ŭ������ ��ӹ޾� override�ϸ� �ȴ�.
* �ڵ� ������ �ƿ� �����Ƿ� addComponent���� ���־���Ѵ�.
*/

class UI_Button : public GameObject
{
protected:
	RectTransform* rectTransform;
	ImageRenderer* imageRenderer;
	// UI�� TextRenerer ����� �߰��ϱ�
	Button* button;

public:
	UI_Button() {}
	~UI_Button() override {}

	void Awake() override {};
	void Start() override {};
	void Update() override {};
	void Destroy() override {};
};

