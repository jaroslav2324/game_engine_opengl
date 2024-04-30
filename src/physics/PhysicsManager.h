#pragma once

#include "../objects/Object.h"
#include "../objects/RigidBody.h"
#include <algorithm>
#include <vector>


class PhysicsManager{

public:

    void addObject(Object* object);
    void removeObject(Object* object);

    void updatePhysics(float dt);

private:

    std::vector<Object*> objects;
};