#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Time.h"

// script component system ���� ��
class Moon : public GameObject
{
private:
	float rotationSpeed = 100.0f;
public:
	Moon() {
		transform = AddComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
	}
	~Moon() override {}
	Transform* transform;
	SpriteRenderer* sr;

	void Awake() override;
	void SceneStart() override;
	void Update() override;
	void Destroyed() override;
};
