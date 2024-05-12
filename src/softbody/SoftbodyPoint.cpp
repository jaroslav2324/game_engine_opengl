#include "SoftbodyPoint.h"

AABB SoftbodyPoint::getCollShapeAABB(){
    float radius = collisionShape.radius;
    return AABB(position.x - radius, position.y - radius, position.x + radius, position.y + radius);
}

void SoftbodyPoint::addForce(Vector2D force)
{
    this->physicsParameters.forceVec += force;
}

void SoftbodyPoint::applyPhysics(float deltaTime){
    // apply gravity
    this->physicsParameters.forceVec += Vector2D(0, G * this->physicsParameters.mass) * this->physicsParameters.gravityScale;

    applyVelocity(deltaTime);

    this->physicsParameters.forceVec.x = 0;
    this->physicsParameters.forceVec.y = 0;
}

void SoftbodyPoint::applyVelocity(float deltaTime){
    // apply velocity
    this->physicsParameters.velocityVec += this->physicsParameters.forceVec / this->physicsParameters.mass;
    position.x += this->physicsParameters.velocityVec.x * deltaTime;
    position.y += this->physicsParameters.velocityVec.y * deltaTime;
}
