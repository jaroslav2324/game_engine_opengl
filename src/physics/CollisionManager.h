#pragma once

#include <vector>

#include "../objects/Circle.h"


class CollisionManager{
public:
    //CollisionManager();
    //~CollisionManager();
    
    void addObject(Object* obj);
    void removeObject(Object* obj);

    void resolveCollisions();

    private:

    bool checkCircleCircleIntersection( Circle& obj1, Circle& obj2);
    bool checkAABBintersection(const AABB& a, const AABB& b);

    std::vector<Object*> collidableObjects;

};
