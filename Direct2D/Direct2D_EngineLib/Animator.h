#pragma once
#include "Component.h"
#include "AnimatorSystem.h"
#include "AnimatorController.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Time.h"

/* [Animator Component]
* GameObject�� �����Ǿ� ������ AnimatorController�� Update��Ű��,
* SpriteRenderer�� sprite�� update���ִ� ������Ʈ
* �� SpriteRenderer�� AnimationController�� �߰��ٸ� ����
* 'Animator'->AnimatorController->State->clip->'sprite'
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
    }  

    void OnEnable() override;
    void Update();
    void OnDestroy() override;

public:
    void SetController(AnimatorController* newController);
};

