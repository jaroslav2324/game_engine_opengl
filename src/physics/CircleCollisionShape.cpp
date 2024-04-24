#include "CircleCollisionShape.h"

float CircleCollisionShape::getRadius(){
    return radius;
}
void CircleCollisionShape::setRadius(float radius){
    this->radius = radius;
}

AABB CircleCollisionShape::getAABB(){
    return AABB(position.x - radius, position.y - radius, position.x + radius, position.y + radius);
}
