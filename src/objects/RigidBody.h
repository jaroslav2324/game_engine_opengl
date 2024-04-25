#pragma once

#include "Object.h"
#include "../physics/PhysicsParameters.h"
#include "../physics/CollisionShape.h"


// RigidBody is a class that represents a rigid body in the physics engine.

class RigidBody{
    public:
    RigidBody(Point2D center) : center(center) {};
    ~RigidBody();
    void setCollisionShape (CollisionShape* collisionShape);
    CollisionShape* getCollisionShape();
    void destroyCollisionShape ();

    virtual void updateRenderedItemsPosition (float dx, float  dy) = 0;
    void applyPhysics(float dt);

    protected:

    void applyVelocity (float dt);
    void applyForces (float dt);
    void applyGravity (float dt);

    Point2D center;

    PhysicsParameters physicsParameters;
    CollisionShape* collisionShape = nullptr;

};