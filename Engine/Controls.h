#pragma once

#include <Tonic/Keys.h>
#include <array>
#include "Direction.h"

namespace Events {
    struct KeyboardInput;
}

class Controls
{
public:
    Controls() : mDirectionInputs{DIRECTION_NONE, DIRECTION_NONE} {}

    void AttachEventHandler(void);
    void DetachEventHandler(void);

    Direction GetMovementDirection(void);

private:
    void HandleDirectionKeys(Events::KeyboardInput &ev);
    void EventHandler(Events::KeyboardInput &ev);

    Direction mDirectionInputs[2];
};