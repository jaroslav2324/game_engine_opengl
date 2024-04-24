#include "CollisionManager.h"

//template <typename T1, typename T2>
bool CollisionManager::checkAABBintersection(const AABB &a, const AABB &b){

    if (a.x > b.x + b.w || a.x + a.w < b.x || a.y > b.y + b.h || a.y + a.h < b.y)
        return false;
    return true;
}

//template <typename T1, typename T2>
bool CollisionManager::checkCircleCircleIntersection(Circle &obj1, Circle &obj2){
    auto shape1 = obj1.getCollisionShape();
    auto shape2 = obj2.getCollisionShape();
    float distance = sqrt(pow(shape1.getPosition().x - shape2.getPosition().x , 2) 
    + pow(shape1.getPosition().y - shape2.getPosition().y , 2));

    if (distance < shape1.getRadius() + shape2.getRadius())
        return true;
    return false;
}
