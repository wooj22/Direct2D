#pragma once
#include "../Direct2D_EngineLib/Script.h"
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/ICollider.h"

class Transform;
class SpriteRenderer;
class AnimatorController;
class WorldTextRenderer;
class Rigidbody;

class CatController : public Script
{
private:
	// stat
	float curSpeed = 0;
	float walkSpeed = 280.f;
	float runSpeed = 350.f;
	float jumpForce = 350.0f;

	// move
	float inputX, inputY;
	bool isGround;

	// key
	bool isW, isA, isD, isShift, isSpace;

	// ref component
	Transform* tr;
	SpriteRenderer* sr;
	Rigidbody* rb;
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

	// trigger
	void OnTriggerEnter(ICollider* other) override { }
	void OnTriggerStay(ICollider* other)  override { }
	void OnTriggerExit(ICollider* other)  override { }

	// collision
	void OnCollisionEnter(ICollider* other, const ContactInfo& contact)  override
	{ 
		if (other->gameObject->name == "Cloud") {
			OutputDebugStringA("OnCollisionEnter() - Could\n");
			isGround = true;
		}
	}

	void OnCollisionStay(ICollider* other, const ContactInfo& contact) override
	{ 
		if (other->gameObject->name == "Cloud") { 
			//OutputDebugStringA("OnCollisionStay() - Could\n");
		}
	}

	void OnCollisionExit(ICollider* other, const ContactInfo& contact)  override
	{ 
		if (other->gameObject->name == "Cloud") {
			OutputDebugStringA("OnCollisionExit() - Could\n");
			isGround = false;
		}
	}

public:
	float GetSpeed() { return curSpeed; }

private:
	void InputCheak();
	void Move_Transform();		// kinematic move
	void Move_Physics();		// physics move
	void Jump_Physics();
	void InfoTextUpdate();
};

