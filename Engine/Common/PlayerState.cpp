#include "PlayerState.h"
#include "Controls.h"
#include <iostream>

void PlayerState::UpdateControls(Controls &controls)
{
    Move(controls.GetMovementDirection(), !mIsStrafing);

    if (controls.Pressed(Tonic::Key::LShift))
        mCombatModeToggled = !mCombatModeToggled;
    
    mCombatModeToggled ? UpdateCombatControls(controls) : UpdateNormalControls(controls);
}

void PlayerState::UpdateCombatControls(Controls &controls)
{
    mIsStrafing = controls.Held(Tonic::Key::X);
}

void PlayerState::UpdateNormalControls(Controls &control)
{
}
