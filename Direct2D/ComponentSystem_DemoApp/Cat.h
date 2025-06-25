#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"
#include "CatController.h"

class Cat : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* sr;
	WorldTextRenderer* tr;
	CatController* catController;

	// TODO ::
	// ���� ScriptConponent ���� GameObject cycle �����ϰ�
	// �����ڿ��� AddComponent �ص� ��
	void Awake() override;
	void Start() override;
	void Update() override;
	void Destroyed() override;
};

