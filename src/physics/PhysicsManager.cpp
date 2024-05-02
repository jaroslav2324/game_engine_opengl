#include "PhysicsManager.h"

void PhysicsManager::addObject(CollidableObject *object){
    objects.push_back(object);
}

void PhysicsManager::removeObject(CollidableObject *object){
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

void PhysicsManager::updatePhysics(float dt){
    for(auto object : objects){
        if (object->getObjectType() == ObjectType::RIGIDBODY){
            ((RigidBody*)object)->applyPhysics(dt);
        }
    }
}
