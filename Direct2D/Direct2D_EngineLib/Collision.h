#pragma once
#include "ICollider.h"
#include "Vector2.h"

/* [Collision]
* ���� �浹 �̺�Ʈ�� block�� �����ϱ� ���� �߰��� �浹 ���� data class
* OnCollisionEnter, Stay, Eixt�� �浹 �߻��� collider��ü���� �ƴ� 
* ���� �浹 �����Ͱ� ��� Collistion��ü�� �����ϸ�, �̸� ���� �浹 ������ �˾Ƴ� block�� �����Ѵ�.
*/

// �ϴ� Contect Info�� �غ���. �̰� �Ⱦ�!

//class Collision
//{
//private:
//    ICollider* thisCollider = nullptr;    // this collider
//
//public:
//    ICollider* otherCollider = nullptr;   // other collider
//    Vector2 contactPoint;                 // �浹 ����
//    Vector2 contactNormal;                // �浹 ����
//    Vector2 relativeVelocity;             // ��� �ӵ�
//
//    Collision(ICollider* _this, ICollider* other) 
//        : thisCollider(_this), otherCollider(other) { }
//
//
//};
//
