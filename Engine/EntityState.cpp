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

void EntityState::Move(Direction dir, bool faceDir)
{
    if (IsMoving())
        return;

    switch (dir)
    {
    case DIRECTION_UP:
        mTargetPos += glm::vec2{0.0f, -16.0f};
        break;
    case DIRECTION_DOWN:
        mTargetPos += glm::vec2{0.0f, 16.0f};
        break;
    case DIRECTION_LEFT:
        mTargetPos += glm::vec2{-16.0f, 0.0f};
        break;
    case DIRECTION_RIGHT:
        mTargetPos += glm::vec2{16.0f, 0.0f};
        break;
    case DIRECTION_NONE:
        mLegState = 1;
        return;
    }

    if (faceDir && dir != DIRECTION_NONE) 
        mFacingDir = dir;
    
    IncrementLegState();
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
