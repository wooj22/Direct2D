#pragma once
#include <Windows.h>
#include "Object.h"

/* [Component]
* ���� ������Ʈ�� ������ ������Ʈ���� Base Class
*/

class GameObject;
class Component : public Object
{
public:
    GameObject* gameObject = nullptr;

public:
    virtual ~Component() = default;

    /* Component Cycle */
    virtual void OnEnable() = 0;    // ������Ʈ Ȱ��ȭ��
    virtual void OnDestroy() = 0;   // ������Ʈ or ���ӿ�����Ʈ �ı���
};

