#pragma once

#include "../objects/Circle.h"


class CollisionManager{
public:
    //CollisionManager();
    //~CollisionManager();

    bool checkCircleCircleIntersection( Circle& obj1, Circle& obj2);

    private:
    bool checkAABBintersection(const AABB& a, const AABB& b);

};
