#pragma once
#include "AnimationClip.h"
#include "AnimationBaseState.h"

/* [AnimatorController Asset]
* 
*/

class AnimatorController
{
public:
    AnimationBaseState* curState = nullptr;
    float currentTime = 0.0f;
    int currentFrameIndex = 0;
    bool playing = false;

public:
    AnimatorController() = default;
    virtual ~AnimatorController() = 0;  // AnimatorContorller���� Clip, State�� �����ϱ� ������ �Ҹ��ڿ��� �����ؾ���

    // Animation State(Clip) Change
    void ChangeAnimation(AnimationBaseState* state)
    {
        if (curState)
            curState->Exit();

        curState = state;
        currentTime = 0.0f;
        currentFrameIndex = 0;
        playing = true;

        if (curState)
            curState->Enter();
    }

    void Update(float deltaTIme)
    {
        if (!curState || !curState->clip || !playing)
            return;

        // loop cheak
        currentTime += deltaTIme;
        if (currentTime >= curState->clip->duration)
        {
            if (curState->clip->loop) currentTime = 0.0f;   
            else
            {
                currentTime = curState->clip->duration;
                playing = false;
            }
        }

        // frame update
        int frameIndex = 0;
        for (size_t i = 0; i < curState->clip->frames.size(); ++i)
        {
            if (currentTime >= curState->clip->frames[i].time)
                frameIndex = (int)i;
            else
                break;
        }

        currentFrameIndex = frameIndex;
        curState->Update(deltaTIme);
    }

    shared_ptr<Sprite> GetCurrentSprite() const
    {
        if (!curState || !curState->clip) return nullptr;
        return curState->clip->frames[currentFrameIndex].sprite;
    }
};

