#include "AABB.h"

bool AABB::intersects(AABB &second){
    return (this->x < second.x + second.w && this->x + this->w > second.x && this->y < second.y 
    + second.h && this->y + this->h > second.y);
}