#pragma once

#include "Object.h"
#include "../physics/PhysicsParameters.h"
#include "../physics/CollisionShape.h"


enum class RigidBodyType {
    CIRCLE,
    RECT,
    UNDEFINED
};


// RigidBody is a class that represents a rigid body in the physics engine.

class RigidBody: public Object{
    public:
    RigidBody(Point2D center, RigidBodyType rigBodyType) : center(center), rigBodyType(rigBodyType), Object(ObjectType::RIGIDBODY) {};
    ~RigidBody();
    void setCollisionShape (CollisionShape* collisionShape);
    CollisionShape* getCollisionShape();
    void destroyCollisionShape ();
    void setPhysicsParameters (PhysicsParameters& physicsParameters);
    PhysicsParameters& getPhysicsParameters();

    RigidBodyType getRigBodyType();
    Point2D getCenter();

    virtual void updateRenderedItemsPosition (float dx, float  dy) = 0;
    void applyPhysics(float dt);
    void setGravityScale(float gs);

    protected:

    void applyVelocity (float dt);
    void applyForces (float dt);
    void applyGravity (float dt);

    Point2D center;

    PhysicsParameters physicsParameters;
    CollisionShape* collisionShape = nullptr;

    RigidBodyType rigBodyType = RigidBodyType::UNDEFINED;

};