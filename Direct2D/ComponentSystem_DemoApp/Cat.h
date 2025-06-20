#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/TextRenderer.h"

class Cat : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* sr;
	TextRenderer* tr;

	// ����� Scene->SceneManager->GameObject ������ ȣ��Ǵ�
	// Cycle�� �����Ͽ� �� �ȿ� conponent ���� ������ �ۼ��ϰ� ������
	// ���� ScriptComponent, ScriptSystem�� �����Ͽ� ����Ƽó��
	// ���ӿ�����Ʈ�� Component�� Get�ؼ� �� ��ɺ� ���� ������ ���� �ۼ��� ����
	// ScriptSystem -> OnEnable, Update, OnDestroy
	// ex) CatController, CatInputSystem ��
	void Awake() override;
	void Start() override;
	void Update() override;
	void Destroy() override;
};

