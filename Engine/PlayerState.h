#pragma once

#include "EntityState.h"

class Controls;

class PlayerState : public EntityState
{
public:
    void UpdateControls(Controls &control);
private:
    void UpdateCombatControls(Controls &control);
    void UpdateNormalControls(Controls &control);
    bool mCombatModeToggled, mIsStrafing;
};