#pragma once
#include <unordered_map>
#include "Component.h"
#include "Vector2.h"

template<typename T>
T clamp(T value, T minVal, T maxVal)		
{
    if (value < minVal) return minVal;
    else if (value > maxVal) return maxVal;
    else return value;
}

/* ContactInfo */
struct ContactInfo
{
	Vector2 point;   // �浹 ����
	Vector2 normal;  // �浹 �������� : �з������� ����(��� �ݶ��̴��� �о�� ����)
};

/* collider type */
enum class ColliderType
{
	Box, Circle
};

/* collider interface */
class ICollider : public Component
{
public:
	// default type
	ColliderType colliderType = ColliderType::Box;

	// collision, trigger
	bool isTrigger = false;             

	// bound
	float minX, maxX, minY, maxY;

	// collision data <�浹�� ��� �ݶ��̴�, �浹����>
	// Enter / Stay / Eixt
	std::unordered_map<ICollider*, ContactInfo> currentFrameCollisions;
	std::unordered_map<ICollider*, ContactInfo> lastFrameCollisions;

	// cycle
	virtual ~ICollider() = default;
	virtual void UpdateBounds() = 0;
	virtual bool isCollision(ICollider* other, ContactInfo& outContact) = 0;
	virtual void FinalizeCollision() = 0;

	// collision event
	virtual void OnCollisionEnter(ICollider* other, ContactInfo& outContact) = 0;
	virtual void OnCollisionStay(ICollider* other, ContactInfo& outContact) = 0;
	virtual void OnCollisionExit(ICollider* other) = 0;
	virtual void OnTriggerEnter(ICollider* other) = 0;
	virtual void OnTriggerStay(ICollider* other) = 0;
	virtual void OnTriggerExit(ICollider* other) = 0;

	// debug draw
	virtual void DebugColliderDraw() {}
};
