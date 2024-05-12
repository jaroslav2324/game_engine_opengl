#include "SoftbodySpring.h"

void SoftbodySpring::updatePhysics(){
    Vector2D diffVec = point1->position - point2->position;
    float distance = diffVec.length();

    float deformLength = distance - restLength;
    float forceVal = stiffness * deformLength;
    Vector2D force = diffVec / distance * forceVal;

    point1->addForce(-force);
    point2->addForce(force);

    Vector2D dampingForce = (point1->physicsParameters.velocityVec - point2->physicsParameters.velocityVec) * damping;
    point1->addForce(-dampingForce);
    point2->addForce(dampingForce);
}