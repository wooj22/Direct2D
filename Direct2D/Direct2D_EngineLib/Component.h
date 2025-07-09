#pragma once
#include <Windows.h>
#include "Object.h"

/* [Component]
* ���� ������Ʈ�� ������ ������Ʈ���� Base Class
* ���� ������Ʈ�� �����ǰ� �ش� ������Ʈ�� ������Ʈ���� ��� ������ ��, OnEnable()�� ȣ��ȴ�.
*/

class GameObject;
class Component : public Object
{
public:
    GameObject* owner = nullptr;

public:
    virtual ~Component() = default;

    /* Component Cycle */
    // ������ 
    virtual void OnEnable() = 0;    // GameObject�� ��� Compoent�� ������ �� �ʱ�ȭ�� ȣ��
    virtual void OnDestroy() = 0;   // GameObject�� �ı��ǰų�, ������Ʈ�� �ı��� �� ȣ��
};

