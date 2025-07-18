#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "DemoApp.h"
#include "Cat.h"
#include "Fish.h"
#include "MenuUIManager.h"
#include "MenuBackground.h"

class MenuScene : public Scene
{
private:
	// menu scene objects
	Camera_Old* camera;
	Cat* cat;
	Fish* fish;
	MenuBackground* background;
	MenuUIManager* menuUIManager;

public:
	MenuScene() = default;
	~MenuScene() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;
};