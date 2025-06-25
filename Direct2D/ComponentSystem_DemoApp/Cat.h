#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"
#include "../Direct2D_EngineLib/Time.h"

class Cat : public GameObject
{
private:
	float moveSpeed = 100.0f;
	float moveDirection = -1.0f;

public:
	Transform* transform;
	SpriteRenderer* sr;
	WorldTextRenderer* tr;

	// TODO :: ScriptComponent, ScriptSystem
	// ����� Scene->SceneManager->GameObject ������ ȣ��Ǵ�
	// Cycle�� �����Ͽ� �� �ȿ� conponent ���� ������ �ۼ��ϰ� ������
	// ���� ScriptComponent, ScriptSystem�� �����Ͽ� ����Ƽó��
	// ���ӿ�����Ʈ�� Component�� Get�ؼ� �� ��ɺ� ���� ������ ���� �ۼ��� ����
	// ScriptSystem -> OnEnable, Update, OnDestroy
	// ex) CatController, CatInputSystem ��
	void Awake() override;
	void Start() override;
	void Update() override;
	void Destroyed() override;

public:
	void Button1Click();
	void Button2Click();
};

