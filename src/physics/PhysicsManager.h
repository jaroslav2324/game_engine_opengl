#pragma once

#include "../objects/CollidableObject.h"
#include "../objects/RigidBody.h"
#include "../objects/Softbody.h"
#include <algorithm>
#include <vector>


class PhysicsManager{

public:

    void addObject(CollidableObject* object);
    void removeObject(CollidableObject* object);

    void updatePhysics(float dt);

private:

    std::vector<CollidableObject*> objects;
};