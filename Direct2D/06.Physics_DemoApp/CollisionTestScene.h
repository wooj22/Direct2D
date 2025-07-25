#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/Camera.h"

#include "DemoApp.h"
#include "ColUIManager.h"
#include "CircleObject.h"
#include "BoxObject.h"
#include "ColObText.h"

class CollisionTestScene : public Scene
{
private:
	GameObject* cam;
	ColUIManager* uiManager;
	BoxObject* box;
	CircleObject* circle;
	ColObText* boxText;
	ColObText* circleText;

	GameObject* parentOb;

public:
	CollisionTestScene() = default;
	~CollisionTestScene() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;

private:
	void ChagneBackScene();
};

