#pragma once
#include "../Direct2D_EngineLib/UI_Button.h"
#include "../Direct2D_EngineLib/UI_Image.h"
#include"../Direct2D_EngineLib/UI_Text.h"
#include "../Direct2D_EngineLib/GameObject.h"

class PlayUIManager : public GameObject
{
public:
    UI_Text* adviceText;
    UI_Button* backButton;

public:
    // game object cycle
    PlayUIManager() {}
    ~PlayUIManager() override {}

    // ������Ʈ�� ������ ��
    void Awake() override             
    {

    }

    // Scene�� Start (���� ��� ������Ʈ�� �����ǰ� �� ��)
    void SceneStart() override     
    {
        adviceText->rectTransform->SetPosition(0, 350);
        adviceText->rectTransform->SetSize(800, 200);
        adviceText->screenTextRenderer->SetFontSize(30);
        adviceText->screenTextRenderer->SetText(L"advide text");
        adviceText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::LightPink));

        backButton->rectTransform->SetPivot(0, 1);
        backButton->rectTransform->SetPosition(-680, 380);
        backButton->rectTransform->SetSize(50, 50);
        backButton->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::LightPink));
        backButton->screenTextRenderer->SetText(L"Back");
        backButton->screenTextRenderer->SetFontSize(20);
    }

    // Scene�� Update
    void Update()  override           
    {
       
    }

    // Scene�� Exit, GameObject Delete
    void Destroyed() override         
    {

    }
};

