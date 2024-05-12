#pragma once

#include "../maths/Vector2D.h"
#include "../physics/gravity.h"

struct SoftbodyPointPhysicsParameters{
    float mass = 1.0f;
    float gravityScale = 1.0f;
    Vector2D forceVec = {0, 0};
    Vector2D velocityVec = {0, 0};
};
