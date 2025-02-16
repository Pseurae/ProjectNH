#pragma once

#include "Direction.h"
#include <glm/vec2.hpp>

class EntityState
{
public:
    void Update(void);
    void Move(Direction dir, bool faceDir = false);
    inline auto GetPosition(void) const { return mCurrentPos; }
    inline void SetPosition(const glm::vec2 &pos) { mCurrentPos = mTargetPos = pos; }
    inline Direction GetFacingDir(void) const { return mFacingDir; }
    inline void SetFacingDir(Direction dir) { mFacingDir = dir; }
    inline bool IsMoving(void) const { return mCurrentPos != mTargetPos; }
    inline int GetLegState(void) const { return mLegState; }

    bool CanMoveTo(const glm::ivec2 &pos);

    void IncrementLegState(void);

private:
    glm::vec2 mCurrentPos{0.0f, 0.0f};
    glm::vec2 mTargetPos{0.0f, 0.0f};
    glm::ivec2 mGridPos{0, 0};
    Direction mFacingDir = DIRECTION_NONE;

    bool mLegDirection = false;
    int mLegState = 1;
};