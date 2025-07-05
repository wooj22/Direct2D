#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Time.h"

#include "CatController.h"
#include "CatAnimatorController.h"

/* Animation ���� - [1][2][3] key�� Animation ��ȯ */
/* FSM ������ �Ǿ������� condition�� ���� ����       */
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

	void Awake() override {}			 // ������Ʈ�� �����ǰ� ��� ������Ʈ�� OnEnable()�� ����� ����
	void SceneStartInit() override {}	 // Scene�� Start
	void Update() override {}			 // Scene�� Update
	void Destroyed() override {}		 // Scene�� Exit, GameObject Delete
};

