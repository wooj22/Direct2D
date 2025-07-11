#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Time.h"

#include "CatController.h"
#include "CatAnimatorController.h"

class Cat : public GameObject
{
public:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	CatController* controller;		// script compoennt
	Animator* animator;

	// animation asset
	CatAnimatorController* catAnimatorController;

public:
	// game object cycle
	Cat() : GameObject("Cat\n")
	{
		OutputDebugStringA("Cat Cat()\n");
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		controller = AddComponent<CatController>();
		animator = AddComponent<Animator>();

		catAnimatorController = new CatAnimatorController();  // animator controller
		animator->SetController(catAnimatorController);
	}
	~Cat() override { delete catAnimatorController; OutputDebugStringA("Cat ~Cat()\n");
	}

	void Awake() { OutputDebugStringA("Cat Awake()\n"); }
	void SceneStart() override
	{
		OutputDebugStringA("Cat SceneStart()\n");
	}
	void Destroyed() { OutputDebugStringA("Cat Destroyed()\n"); }
};

