#include "Button.h"

void Button::OnEnable() 
{

}

void Button::Update() 
{
	OnClick();
}

void Button::OnDestroy() 
{

}

inline void Button::OnClick()
{
	// ���� �� ��ư�� Ŭ���ƴٸ�
	onClickListeners.Invoke();
}