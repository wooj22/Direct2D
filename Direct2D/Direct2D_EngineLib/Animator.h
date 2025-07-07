#pragma once
#include "Component.h"
#include "AnimatorSystem.h"

/* [Animator Component]
* GameObject�� �����Ǿ� ������ AnimatorController�� Update��Ű��,
* SpriteRenderer�� sprite�� update���ִ� ������Ʈ
* �� SpriteRenderer�� AnimationController�� �߰��ٸ� ����
* 'Animator'->AnimatorController->State->clip->'sprite'
*/

class AnimatorController;
class SpriteRenderer;

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
    }  

    void OnEnable() override;
    void Update();
    void OnDestroy() override;

public:
    void SetController(AnimatorController* newController);
};

