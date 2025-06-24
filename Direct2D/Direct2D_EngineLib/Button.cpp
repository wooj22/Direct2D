#include "Button.h"
#include "GameObject.h"
#include "Input.h"

void Button::OnEnable() 
{
    rectTransform = this->owner->GetComponent<RectTransform>();
}

void Button::Update() 
{
    if (!rectTransform) return;

    // 1. ���콺 Ŭ�� ����
    if (!Input::GetKeyDown(VK_LBUTTON)) return;

    // 2. ���콺 ��ġ �������� (Ŭ���̾�Ʈ ��ǥ��)
    POINT mouse = Input::GetMousePosition();
    float mouseX = static_cast<float>(mouse.x);
    float mouseY = static_cast<float>(mouse.y);

    // 3. ��ư ���� ��� (pivot ������ screen ����)
    D2D1_POINT_2F pos = rectTransform->GetPosition();
    D2D1_SIZE_F size = rectTransform->GetSize();
    D2D1_POINT_2F pivot = rectTransform->GetPivot();

    float left = pos.x - (size.width * pivot.x);
    float top = pos.y - (size.height * pivot.y);
    float right = left + size.width;
    float bottom = top + size.height;

    // 4. ���콺�� ��ư ���� �ȿ� �ִ��� Ȯ��
    if (mouseX >= left && mouseX <= right &&
        mouseY >= top && mouseY <= bottom)
    {
        OnClick();  // Ŭ�� �̺�Ʈ ȣ��
    }
}

void Button::OnDestroy() 
{

}

inline void Button::OnClick()
{
    OutputDebugStringA("Button OnClick() �̺�Ʈ �߻�! �ݹ��Լ� ȣ��.\n");
	onClickListeners.Invoke();
}