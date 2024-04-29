#pragma once 

#include "../maths/Vector2D.h"

#define G 9.81

// struct for physics parameters
struct PhysicsParameters
{
    bool staticBody = false;
    float gravityScale = 1;
    float mass = 100;
    Vector2D forceVector = {0, 0};
    Vector2D velocityVector = {0, 0};
    // Vector2D angularVelocityVector = {0, 0};
};
