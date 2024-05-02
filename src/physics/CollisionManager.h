#pragma once

#include <vector>

#include "../objects/Circle.h"
#include "../objects/Rect.h"


class CollisionManager{
public:
    //CollisionManager();
    //~CollisionManager();
    
    void addObject(CollidableObject* obj);
    void removeObject(CollidableObject* obj);

    void resolveCollisions();

    private:

    void resolveRigidRigidCollision(RigidBody& obj1, RigidBody& obj2);
    void resolveCircleCircleCollision(Circle& cir1, Circle& cir2);
    void resolveCircleRectCollision(Circle& obj1, Rect& obj2); 
    void resolveRectRectCollision(Rect& obj1, Rect& obj2);

    bool checkCircleCircleIntersection( Circle& obj1, Circle& obj2);
    bool checkCircleRectIntersection (Circle& obj1, Rect& obj2);
    bool checkAABBintersection(const AABB& a, const AABB& b);

    std::vector<CollidableObject*> collidableObjects;

};
