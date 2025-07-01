#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "DemoApp.h"
#include "Cat.h"
#include "../Direct2D_EngineLib/UI_Image.h"
#include "../Direct2D_EngineLib/UI_Text.h"
#include "../Direct2D_EngineLib/UI_Button.h"

/* ���ҽ� �����ڿ� �޸� �׽�Ʈ �� - ��ư Ŭ��*/
class Scene2 : public Scene
{
private:
	Camera* camera;
	UI_Image* titleBackground;
	UI_Text* titleText;
	UI_Text* adviceText;
	UI_Text* memoryUsageText;
	UI_Button* createButton;
	UI_Button* deleteButton;

public:
	Scene2() = default;
	~Scene2() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;

private:
	// ���ҽ� ���������� ����	test �Լ�
	void Scene2ObjectCreate();
	void Scene2ObjectSetting();

	void CreateButtonClick();
	void DeleteButtonClick();
};

