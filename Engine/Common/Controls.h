#pragma once

#include <Tonic/Keys.h>
#include <array>
#include <map>
#include "Direction.h"

namespace Events {
    struct KeyboardInput;
}

class Controls
{
public:
    Controls() = default;

    void AttachEventHandler(void);
    void DetachEventHandler(void);

    Direction GetMovementDirection(void) const;
    void SwapKeyStates(void);

    inline bool Pressed(Tonic::Key key) { return mCurrentKeys[key] && !mLastKeys[key]; }
    inline bool Released(Tonic::Key key) { return !mCurrentKeys[key] && mLastKeys[key]; }
    inline bool Held(Tonic::Key key) { return mCurrentKeys[key] && mLastKeys[key]; }

private:
    void HandleDirectionKeys(Events::KeyboardInput &ev);
    void HandleOtherKeys(Events::KeyboardInput &ev);
    void EventHandler(Events::KeyboardInput &ev);

    Direction mDirectionInputs[2] = {DIRECTION_NONE, DIRECTION_NONE};
    std::map<Tonic::Key, bool> mCurrentKeys, mLastKeys;
};