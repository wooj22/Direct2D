#pragma once
#include "Component.h"
#include "AnimatorController.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Time.h"

/* [Animator Component]
* GameObject�� �����Ǿ� AnimatorController�� �����Ű��,
* SpriteRenderer�� sprite�� ������Ʈ���ִ� ������Ʈ
* Animator->AnimatorController->State->clip
*/

class Animator : public Component
{
public:
    AnimatorController* controller;
    SpriteRenderer* spriteRenderer;

    Animator() = default;
    ~Animator() override { delete controller; }  // Controller�� new�� ���������� �Ҹ��ڿ��� ����

    void OnEnable() override
    {
        spriteRenderer = owner->GetComponent<SpriteRenderer>();
    }

    // Update
    void Update()
    {
        if (!controller) return;

        // animation update (controller->state->clip)
        controller->Update(Time::GetDeltaTime());

        // sprite update
        spriteRenderer->sprite = controller->GetCurrentSprite();
    }

    // Set Animator Controller
    void SetController(AnimatorController* newController)
    {
        if (controller) delete controller;
        controller = newController;
    }
};

