#pragma once
#include "AnimationClip.h"

/* [AnimationBaseState]
* AnimatorController�� FSM�� ��ϵ� Base State
* ���� ���������� Animation Clip�� State�� �����ϰ�, FSM ���� ��ȯ ������ �ۼ��ϸ� �ȴ�.
*/

class AnimationBaseState
{
public:
    AnimationClip* clip = nullptr;

    AnimationBaseState(AnimationClip* c) : clip(c) {}
    virtual ~AnimationBaseState() = default;

    virtual void Enter() = 0;
    virtual void Update(float dt) = 0;
    virtual void Exit() = 0;
};

