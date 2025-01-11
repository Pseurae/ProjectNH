#pragma once

#include "EntityState.h"

class Controls;

class PlayerState : public EntityState
{
public:
    void UpdateControls(Controls &control);
    [[nodiscard]] inline bool IsCombatModeToggled(void) const { return mCombatModeToggled; }
    [[nodiscard]] inline bool IsStrafing(void) const { return mIsStrafing; }
private:
    void UpdateCombatControls(Controls &control);
    void UpdateNormalControls(Controls &control);
    bool mCombatModeToggled = false, mIsStrafing = false;
};