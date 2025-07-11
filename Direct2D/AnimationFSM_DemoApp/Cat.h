#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Time.h"

#include "CatController.h"
#include "CatAnimatorController.h"

/* Animation FSM condition & transition 과제 */
// Animator -> AnimatorController -> State -> AnimationClip
class Cat : public GameObject
{
private:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	CatController* controller;
	Animator* animator;

	// animation asset
	CatAnimatorController* catAnimatorController;

public:
	// game object cycle
	Cat() : GameObject("Cat")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		controller = AddComponent<CatController>();
		animator = AddComponent<Animator>();

		catAnimatorController = new CatAnimatorController();  // animator controller
		animator->SetController(catAnimatorController);
	}
	~Cat() override { delete catAnimatorController; }

	void Awake() override {}			 // 오브젝트가 생성되고 모든 컴포넌트의 OnEnable()이 실행된 이후
	void SceneStart() override {}	 // Scene의 Start
	void Update() override {}			 // Scene의 Update
	void Destroyed() override {}		 // Scene의 Exit, GameObject Delete
};

