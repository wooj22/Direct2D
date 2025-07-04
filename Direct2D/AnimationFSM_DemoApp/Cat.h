#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "CatController.h"
#include "../Direct2D_EngineLib/Time.h"

// test
//#include "CatIdleClip.h"

class Cat : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	CatController* controller;
	//CatIdleClip idle;

	Cat() : GameObject("Cat")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		controller = AddComponent<CatController>();
	}
	~Cat() override {}

	/* GameObject Cycle */
	void Awake() override				 // ������Ʈ�� �����ǰ� ��� ������Ʈ�� OnEnable()�� ����� ����
	{
		// resource create
		auto catTexture = ResourceManager::Get().CreateTexture2D("../Resource/Texture/Cat_Idle.png");
		auto new_sprite = ResourceManager::Get().CreateSprite(catTexture, "Cat_Idle");
		spriteRenderer->sprite = new_sprite;
	}
	void SceneStartInit() override {}	 // Scene�� Start
	void Update() override {}			 // Scene�� Update
	void Destroyed() override {}		 // Scene�� Exit, GameObject Delete
};

