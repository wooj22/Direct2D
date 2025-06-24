#pragma once
#include "Component.h"
#include "RectTransform.h"
#include "MultiDelegate.h"
#include "ButtonSystem.h"

/* [Button Conponent]
* onClick() �̺�Ʈ�� �����ϰ� �߻��ϴ� ������Ʈ
* RectTransform�� ������ GameObject�� ��ϵǾ�� �������� Button�� ����� Ȱ���� �� �ִ�.
*/

class Button : public Component
{
private:
    RectTransform* rectTransform;     // button ���� get

public:
    MultiDelegate<> onClickListeners; // callback functions

public:
    // component cycle
    Button() { ButtonSystem::Get().Regist(this); }
    ~Button() override { ButtonSystem::Get().Unregist(this); }

    void OnEnable() override;
    void Update();
    void OnDestroy() override;

private:
    void OnClick(); // event
};

