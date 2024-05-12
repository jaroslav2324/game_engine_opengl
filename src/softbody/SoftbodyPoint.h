#pragma once

#include "../maths/Point2D.h"
#include "../physics/SoftbodyPointPhysicsParameters.h"
#include "../physics/AABB.h"
#include "SoftbodyPointCollisionShape.h"

struct SoftbodyPoint{

    SoftbodyPoint(Point2D pos): position(pos){};
    Point2D position;
    SoftbodyPointCollisionShape collisionShape;                                                                                                                              
    SoftbodyPointPhysicsParameters physicsParameters;

    AABB getCollShapeAABB();

    void addForce(Vector2D force);
    void applyPhysics(float deltaTime);
    void applyVelocity(float deltaTime);
};
