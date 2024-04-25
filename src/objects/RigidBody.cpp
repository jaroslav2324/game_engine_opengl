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

    auto collisionCenter = collisionShape->getPosition();
    collisionCenter.x += physicsParameters.velocityVector.x * dt;
    collisionCenter.y += physicsParameters.velocityVector.y * dt;
    collisionShape->setPosition(collisionCenter);

    // Update the rendered triangles
    updateRenderedItemsPosition(physicsParameters.velocityVector.x * dt, 
    physicsParameters.velocityVector.y * dt);

}

void RigidBody::applyGravity(float dt){
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
    destroyCollisionShape();
}

void RigidBody::setCollisionShape(CollisionShape *collisionShape){
    if ( this->collisionShape != nullptr ) {
        delete this->collisionShape;
    }
    this->collisionShape = collisionShape;
}

CollisionShape *RigidBody::getCollisionShape(){
    return collisionShape;
}

void RigidBody::destroyCollisionShape(){
    if (collisionShape != nullptr) {
        delete collisionShape;
        collisionShape = nullptr;
    }
}

void RigidBody::applyPhysics(float dt)
{
    applyVelocity(dt);
    applyForces(dt);
}