#pragma once
#include "Component.h"
#include "AnimatorSystem.h"
#include "AnimatorController.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Time.h"

/* [Animator Component]
* GameObject�� �����Ǿ� AnimatorController�� �����Ű��,
* SpriteRenderer�� sprite�� ������Ʈ���ִ� ������Ʈ
* Animator->AnimatorController->State->clip
*/

class AnimatorSystem;
class Animator : public Component
{
public:
    AnimatorController* controller = nullptr;
    SpriteRenderer* spriteRenderer = nullptr;

public:
    // component cycle
    Animator() 
    { 
        AnimatorSystem::Get().Regist(this);
    }
    ~Animator() override 
    { 
        AnimatorSystem::Get().Unregist(this);
        //delete controller;  ���ҽ� �Ŵ��� ������ �ٲٱ�
    }  

    void OnEnable() override;
    void Update();
    void OnDestroy() override;

public:
    void SetController(AnimatorController* newController);
};

