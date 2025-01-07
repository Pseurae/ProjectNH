#include "EntityState.h"
#include <glm/glm.hpp>
#include "Global.h"

static glm::vec2 MoveTowards(const glm::vec2 &current, const glm::vec2 &target, float maxDistDelta)
{
    glm::vec2 a = target - current;
    float magnitude = glm::length(a);
    if (magnitude <= maxDistDelta || magnitude == 0.0f)
    {
        return target;
    }
    return current + a / magnitude * maxDistDelta;
}

void EntityState::Update(void)
{
    mCurrentPos = MoveTowards(mCurrentPos, mTargetPos, global.deltaTime * 100);
}

static const glm::ivec2 sDirectionVectors[] =
{
    glm::ivec2{0, -1},  // DIRECTION_UP
    glm::ivec2{0, 1},   // DIRECTION_DOWN
    glm::ivec2{-1, 0},  // DIRECTION_LEFT
    glm::ivec2{1, 0},   // DIRECTION_RIGHT
    glm::ivec2{0, 0}    // DIRECTION_NONE
};

void EntityState::Move(Direction dir, bool faceDir)
{
    if (IsMoving())
        return;

    if (CanMoveTo(mGridPos + sDirectionVectors[dir]))
    {
        mGridPos += sDirectionVectors[dir];
        mTargetPos += (glm::vec2)sDirectionVectors[dir] * 16.0f;
    }

    if (dir == DIRECTION_NONE)
    {
        mLegState = 1;
        return;
    }

    if (faceDir && dir != DIRECTION_NONE) 
        mFacingDir = dir;
    
    IncrementLegState();
}

bool EntityState::CanMoveTo(const glm::ivec2 &pos)
{
    return !global.game->GetMap().IsOutOfBounds(pos);
}

void EntityState::IncrementLegState(void)
{
    if (mLegDirection)
    {
        if (++mLegState >= 2) 
        {
            mLegDirection = !mLegDirection;
            mLegState = 2;
        }
    }
    else
    {
        if (--mLegState <= 0)
        {
            mLegDirection = !mLegDirection;
            mLegState = 0;
        }
    }
}
