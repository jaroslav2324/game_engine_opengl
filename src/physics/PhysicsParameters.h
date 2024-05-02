#pragma once 

#include <iostream>
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

    // coeff must be from 0 to 1
    int setElastic(float coeffElasticity);
    void unsetElastic();
    bool isElastic();
    float getCoeffElasticity();

    private:
    bool elasticBody = false;
    float coeffElasticity = 0;
};
