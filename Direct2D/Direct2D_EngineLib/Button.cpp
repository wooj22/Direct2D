#include "Button.h"
#include "RectTransform.h"
#include "ImageRenderer.h"
#include "GameObject.h"
#include "Input.h"
#include <iostream>
#include <string>

void Button::OnEnable() 
{
    rectTransform = this->owner->GetComponent<RectTransform>();
}

void Button::Update() 
{
    if (!rectTransform) return;

    // 1. 마우스 클릭 감지
    if (!Input::GetKeyDown(VK_LBUTTON)) return;

    // 2. 마우스 위치 가져오기 (클라이언트 좌표계)
    POINT mouse = Input::ConvertMouseToUnityPosition();
    float mouseX = static_cast<float>(mouse.x);
    float mouseY = static_cast<float>(mouse.y);

    // 3. 버튼 영역 계산 (pivot 보정된 screen 영역)
    Vector2 pos = rectTransform->GetPosition();
    D2D1_SIZE_F size = rectTransform->GetSize();
    D2D1_POINT_2F pivot = rectTransform->GetPivot();

    float left = pos.x - (size.width * pivot.x);
    float top = pos.y - (size.height * pivot.y);
    float right = left + size.width;
    float bottom = top + size.height;

    // 4. 마우스가 버튼 영역 안에 있는지 확인
    if (mouseX >= left && mouseX <= right &&
        mouseY >= top && mouseY <= bottom)
    {
        OnClick();  // 클릭 이벤트 호출
    }
}

void Button::OnDestroy() 
{

}

inline void Button::OnClick()
{
    OutputDebugStringA("Button OnClick() 이벤트 발생! 콜백함수 호출.\n");
	
    // debug
    std::string str1 = std::to_string(Input::ConvertMouseToUnityPosition().x);
    std::string str2 = std::to_string(Input::ConvertMouseToUnityPosition().y);
    OutputDebugStringA(str1.c_str());
    OutputDebugStringA(" ");
    OutputDebugStringA(str2.c_str());
    OutputDebugStringA("\n");


    onClickListeners.Invoke();
}