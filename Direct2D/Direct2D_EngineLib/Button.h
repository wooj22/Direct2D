#pragma once
#include "Component.h"
#include "MultiDelegate.h"
#include "ButtonSystem.h"

/* [Button Conponent]
* <UI>�� ���� ������ OnClick() �̺�Ʈ�� �����ϰ� �߻���Ű�ϴ� ������Ʈ
* �̺�Ʈ �߻��� onClickListeners�� ��ϵ� �ݹ� �Լ��� ��� ȣ���Ų��.
* RectTransform�� ������ GameObject�� ��ϵǾ�� �������� Button�� ����� Ȱ���� �� �ִ�.
*/

class RectTransform;
class Button : public Component
{
private:
    RectTransform* rectTransform;     // button ���� get

public:
    MultiDelegate<> onClickListeners; // callback functions

public:
    // component cycle
    Button() 
    { 
        ButtonSystem::Get().Regist(this); 
        OutputDebugStringA("Button()\n");
    }
    ~Button() override
    {
        ButtonSystem::Get().Unregist(this); 
        OutputDebugStringA("~Button()\n");
    }

    void OnEnable() override;
    void Update();
    void OnDestroy() override;

private:
    void OnClick(); // event
};

