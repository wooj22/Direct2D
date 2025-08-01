#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/BoxCollider.h"
#include "../Direct2D_EngineLib/CircleCollider.h"

class Cloud : public GameObject
{
public:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	BoxCollider* collider;

public:
	Cloud() : GameObject("Cloud")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		collider = AddComponent<BoxCollider>();

		auto cloud = ResourceManager::Get().CreateTexture2D("../Resource/Cloud.png");
		spriteRenderer->sprite = ResourceManager::Get().CreateSprite(cloud, "Cloud");
	
		OutputDebugString(L"<< Cloud Create >>\n");
	}
	~Cloud() override { OutputDebugString(L"<< Cloud Delete >>\n"); }

	void Awake() override
	{
		collider->size = { spriteRenderer->sprite->size.width-40,
			spriteRenderer->sprite->size.height-90 };
		//collider->radius = 30;
		collider->offset = { 0, -30 };
		collider->isTrigger = false;
	}

	void Update() override
	{
		collider->DebugColliderDraw();
	}
};

