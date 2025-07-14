#pragma once
#include "../Direct2D_EngineLib/Script.h"

class Transform;
class SpriteRenderer;
class AnimatorController;
class WorldTextRenderer;

class CatController : public Script
{
private:
	// stat
	float curSpeed = 0;
	float walkSpeed = 5.f;
	float runSpeed = 10.f;

	// key
	bool isW, isA, isS, isD, isShift;

	// ref component
	Transform* tr;
	SpriteRenderer* sr;
	AnimatorController* ac;

public:
	WorldTextRenderer* infoText;

public:
	// script component cycle
	void OnEnable() override;				// ������Ʈ Ȱ��ȭ ����
	void Awake() override;					// ������Ʈ�� ��� ������Ʈ�� ������ ���� ���� 1ȸ ȣ��
	void Start() override;					// Awake() ���� ���� 1ȸ ȣ��
	void Update() override;					// �� ������ �ݺ� ȣ��
	void FixedUpdate() override;			// ���� ������Ʈ 0.02f ���� �ݺ� ȣ��
	void OnDestroy() override;				// ������Ʈ or ������Ʈ �Ҹ� ����

	/* Collition Event */
	// trigger
	void OnTriggerEnter(ICollider* other) override { OutputDebugStringA("OnTriggerEnter()\n"); }
	void OnTriggerStay(ICollider* other)  override { OutputDebugStringA("OnTriggerStay()\n"); }
	void OnTriggerExit(ICollider* other)  override { OutputDebugStringA("OnTriggerExit()\n"); }

	// collision
	void OnCollisionEnter(ICollider* other)  override { OutputDebugStringA("OnCollisionEnter()\n"); }
	void OnCollisionStay(ICollider* other) override { OutputDebugStringA("OnCollisionStay()\n"); }
	void OnCollisionExit(ICollider* other)  override { OutputDebugStringA("OnCollisionExit()\n"); }

public:
	float GetSpeed() { return curSpeed; }

private:
	void InputCheak();
	void InfoTextUpdate();
};

