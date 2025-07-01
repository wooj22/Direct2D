#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "DemoApp.h"
#include "Cat.h"
#include"../Direct2D_EngineLib/UI_Image.h"
#include"../Direct2D_EngineLib/UI_Text.h"

/* ���ҽ� �����ڿ� �޸� �׽�Ʈ �� - Ű �Է�*/
class Scene1 : public Scene
{
private:
	Camera* camera;
	UI_Image* titleBackground;
	UI_Text* titleText;
	UI_Text* adviceText;
	UI_Text* memoryUsageText;

public:
	Scene1() = default;
	~Scene1() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;

private:
	// ���ҽ� ���������� ����	test �Լ�
	void Scene1ObjectCreate();
	void Scene1ObjectSetting();
};

