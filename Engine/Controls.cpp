#include "Global.h"
#include "Controls.h"
#include "InternalEvents.h"

void Controls::AttachEventHandler(void)
{
    global.eventBus.Register<Events::KeyboardInput, &Controls::EventHandler>(this);
}

void Controls::DetachEventHandler(void)
{
    global.eventBus.Remove<Events::KeyboardInput, &Controls::EventHandler>(this);
}

Direction Controls::GetMovementDirection(void) const
{
    if (mDirectionInputs[1] != DIRECTION_NONE)
        return mDirectionInputs[1];
    return mDirectionInputs[0];
}

void Controls::SwapKeyStates(void)
{
    mLastKeys = mCurrentKeys;
}

static const Tonic::Key sMovementKeys[4] =
{
    Tonic::Key::Up,
    Tonic::Key::Down,
    Tonic::Key::Left,
    Tonic::Key::Right,
};

static const Direction sOppositeDirections[4] = 
{
    DIRECTION_DOWN,
    DIRECTION_UP,
    DIRECTION_RIGHT,
    DIRECTION_LEFT
};

void Controls::HandleDirectionKeys(Events::KeyboardInput &ev)
{
    for (int i = DIRECTION_UP; i <= DIRECTION_RIGHT; ++i)
    {
        if (sMovementKeys[i] != ev.key)
            continue;

        if (ev.action == Tonic::Action::Press)
        {
            if (mDirectionInputs[0] == DIRECTION_NONE)
                mDirectionInputs[0] = i;
            else if (mDirectionInputs[0] != i && mDirectionInputs[1] == DIRECTION_NONE)
                mDirectionInputs[1] = i;   
        }
        else
        {
            if (mDirectionInputs[1] == i) mDirectionInputs[1] = DIRECTION_NONE;
            else if (mDirectionInputs[0] == i)
            {
                mDirectionInputs[0] = mDirectionInputs[1];
                mDirectionInputs[1] = DIRECTION_NONE;
            }
        }
    }

    if (mDirectionInputs[1] != DIRECTION_NONE && 
        sOppositeDirections[mDirectionInputs[1]] == mDirectionInputs[0])
    {
        mDirectionInputs[0] = DIRECTION_NONE;
        mDirectionInputs[1] = DIRECTION_NONE;
    }
}

void Controls::HandleOtherKeys(Events::KeyboardInput &ev)
{
    mCurrentKeys[ev.key] = ev.action == Tonic::Action::Press;
}

void Controls::EventHandler(Events::KeyboardInput &ev)
{
    HandleDirectionKeys(ev);
    HandleOtherKeys(ev);
}
