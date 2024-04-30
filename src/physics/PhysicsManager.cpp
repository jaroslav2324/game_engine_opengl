#include "PhysicsManager.h"

void PhysicsManager::addObject(Object *object){
    objects.push_back(object);
}

void PhysicsManager::removeObject(Object *object){
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

void PhysicsManager::updatePhysics(float dt){
    for(auto object : objects){
        if (object->getObjectType() == ObjectType::RIGIDBODY){
            ((RigidBody*)object)->applyPhysics(dt);
        }
    }
}
