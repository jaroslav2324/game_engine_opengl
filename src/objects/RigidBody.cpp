#include "RigidBody.h"
// Function to apply velocity to the circle and update its position
void RigidBody::applyVelocity(float dt){

    if (physicsParameters.staticBody == true){
        physicsParameters.velocityVector.x = 0;
        physicsParameters.velocityVector.y = 0;
        return;
    }

    center.x += physicsParameters.velocityVector.x * dt;
    center.y += physicsParameters.velocityVector.y * dt;

    // std::cout << "center: " << center.x << " " << center.y << std::endl;

    auto collisionCenter = collisionShape->getPosition();
    collisionCenter.x += physicsParameters.velocityVector.x * dt;
    collisionCenter.y += physicsParameters.velocityVector.y * dt;
    collisionShape->setPosition(collisionCenter);

    // Update the rendered triangles
    updateRenderedItemsPosition(physicsParameters.velocityVector.x * dt, 
    physicsParameters.velocityVector.y * dt);
}

void RigidBody::applyGravity(float dt){
    if (physicsParameters.gravityScale == 0) return;
    physicsParameters.forceVector.y += G * physicsParameters.mass * physicsParameters.gravityScale * dt;
}

void RigidBody::applyForces(float dt)
{
    if (physicsParameters.staticBody == true){
        physicsParameters.forceVector.x = 0;
        physicsParameters.forceVector.y = 0;
        return;
    }
    // change velocity based on force
    physicsParameters.velocityVector.x += physicsParameters.forceVector.x * dt;
    physicsParameters.velocityVector.y += physicsParameters.forceVector.y * dt;
    //std::cout << physicsParameters.velocityVector.x << " " << physicsParameters.velocityVector.y << std::endl;

    // reset force vector

    physicsParameters.forceVector.x = 0;
    physicsParameters.forceVector.y = 0;
    applyGravity(dt);
    // apply other forces
}

RigidBody::~RigidBody(){
    
}


void RigidBody::setPhysicsParameters(PhysicsParameters &physicsParameters){
    this->physicsParameters = physicsParameters;
}

PhysicsParameters &RigidBody::getPhysicsParameters(){
    return physicsParameters;
}

RigidBodyType RigidBody::getRigBodyType(){
    return rigBodyType;
}

Point2D RigidBody::getCenter(){
    return center;
}

Vector2D RigidBody::getVelocity(){
    return physicsParameters.velocityVector;
}

float RigidBody::getMass(){
    return physicsParameters.mass; 
}

void RigidBody::setCenter(Point2D center){
    this->center = center;
}

void RigidBody::setVelocity(Vector2D velocity){
    physicsParameters.velocityVector = velocity;
}

void RigidBody::setMass(float mass){
    physicsParameters.mass = mass;
}

void RigidBody::shift(Vector2D shiftVec){
    center.x += shiftVec.x;
    center.y += shiftVec.y;
}

void RigidBody::applyPhysics(float dt)
{
    applyVelocity(dt);
    applyForces(dt);
}

void RigidBody::setGravityScale(float gs){
    this->physicsParameters.gravityScale = gs;
}

void RigidBody::setStatic(bool val){
    this->physicsParameters.staticBody = val;
}
