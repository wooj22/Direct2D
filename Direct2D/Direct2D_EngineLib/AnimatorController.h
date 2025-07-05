#pragma once
#include "AnimationClip.h"
#include "AnimationBaseState.h"

/* [AnimatorController Asset]
* Animation State Machine (FSM)
* State�� �����ϸ�, ���� AnimationClip�� �������� ����Ѵ�.
* AnimationState���� ������ State�� ��ȯ�Ͽ�, State�� Enter(), Update(), Exit()�� ȣ���Ѵ�.
* ���� ���������� �� class�� ��ӹ��� AnimationController�� �����Ͽ� Ȱ���Ѵ�.
* TODO :: set int/flaot/bool/trigger
* ex) class PlayerAnimationController : public AnimatorController{}
*     -> �� �ȿ��� animation clip�� state�� �����ϸ� �ȴ�.
*        �׷� GameObject�ʿ����� �̸� ������ ��Ʈ�ѷ��� ������Ű�� ����ϰ� ������
*/

class AnimatorController
{
public:
    AnimationBaseState* curState = nullptr;     // animation clip state
    float currentTime = 0.0f;                   // current time (clip start time cheak)
    int currentFrameIndex = 0;                  // current frame
    bool playing = false;                       // loop/stop

private:
    unordered_map<string, AnimationBaseState*> map_state;    // clip state map <name, state>

public:
    AnimatorController() = default;
    virtual ~AnimatorController() = default;

    // frame update
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

    // add state
    void AddState(AnimationBaseState* state)
    {
        string name = state->clip->name;
        map_state[name] = state;
    }

    // play animation with clip name
    void PlayAnimation(const string& clipName)
    {
        auto it = map_state.find(clipName);
        if (it != map_state.end()) 
            ChangeAnimation(it->second);
        else
            OutputDebugStringA(("clip name�� �����ϴ�. " + clipName + "\n").c_str());
    }

    // animation state(Clip) change
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

    // get sprite
    shared_ptr<Sprite> GetCurrentSprite() const
    {
        if (!curState || !curState->clip) return nullptr;
        return curState->clip->frames[currentFrameIndex].sprite;
    }
};

