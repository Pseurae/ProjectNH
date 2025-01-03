#pragma once

#include "Direction.h"
#include <glm/vec2.hpp>

class EntityState
{
public:
    void Update(void);
    void Move(Direction dir);
    auto GetPosition() const { return mCurrentPos; }

private:
    glm::vec2 mCurrentPos{0.0f, 0.0f};
    glm::vec2 mTargetPos{0.0f, 0.0f};
};