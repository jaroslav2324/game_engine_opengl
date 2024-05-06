#pragma once
#include <functional>

#include "CollidableObject.h"
#include "../physics/PhysicsParameters.h"


enum class RigidBodyType {
    CIRCLE,
    RECT,
    UNDEFINED
};


// RigidBody is a class that represents a rigid body in the physics engine.

class RigidBody: public CollidableObject{
    public:
    RigidBody(Point2D center, RigidBodyType rigBodyType) : center(center), rigBodyType(rigBodyType), CollidableObject(ObjectType::RIGIDBODY) {};
    ~RigidBody();

    void setPhysicsParameters (PhysicsParameters& physicsParameters);
    PhysicsParameters& getPhysicsParameters();

    RigidBodyType getRigBodyType();
    Point2D getCenter();
    Vector2D getVelocity();
    float getMass();
    void setCenter(Point2D center);
    void setVelocity(Vector2D velocity);
    void setMass(float mass);

    virtual void updateRenderedItemsPosition (float dx, float  dy) = 0;
    void shift(Vector2D shiftVec);
    void applyPhysics(float dt);
    void setGravityScale(float gs);
    void setStatic(bool val);
    bool isStatic();
    bool isElastic();
    int setElastic(float coeffElasticity);
    float getElasticityCoeff();

    void setOnCollisionCallback(std::function<void ()> callback);
    void callOnCollisionCallback();

    protected:

    void applyVelocity (float dt);
    void applyForces (float dt);
    void applyGravity (float dt);

    std::function<void ()> onCollisionCallback;

    Point2D center;
    PhysicsParameters physicsParameters;

    RigidBodyType rigBodyType = RigidBodyType::UNDEFINED;

};