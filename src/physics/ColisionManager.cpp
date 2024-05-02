#include "CollisionManager.h"

bool CollisionManager::checkAABBintersection(const AABB &a, const AABB &b){

    if (a.x > b.x + b.w || a.x + a.w < b.x || a.y > b.y + b.h || a.y + a.h < b.y)
        return false;
    return true;
}

void CollisionManager::calcVelocitiesMomentumConservation(float mass1, float mass2, float vel1, float vel2, 
float &retVel1, float &retVel2){

    float totalMass = mass1 + mass2;
    retVel1 = ((mass1 - mass2) * vel1  + 2 * mass2 * vel2) / totalMass;
    retVel2 = ((mass2 - mass1) * vel2  + 2 * mass1 * vel1) / totalMass;
}

//TODO implement
void CollisionManager::resolveRigidRigidCollision(RigidBody &obj1, RigidBody &obj2){

    RigidBodyType rigType1 = obj1.getRigBodyType();
    RigidBodyType rigType2 = obj2.getRigBodyType();

    if (rigType1 == RigidBodyType::CIRCLE && rigType2 == RigidBodyType::CIRCLE){
        resolveCircleCircleCollision((Circle&)obj1, (Circle&)obj2); 
    }
    else if (rigType1 == RigidBodyType::CIRCLE && rigType2 == RigidBodyType::RECT){
        resolveCircleRectCollision((Circle&)obj1, (Rect&)obj2); 
    }
    else if (rigType1 == RigidBodyType::RECT && rigType2 == RigidBodyType::RECT){
        resolveRectRectCollision((Rect&)obj1, (Rect&)obj2);
    }
    // TODO: add UNDEFINED handling
}

void CollisionManager::resolveCircleCircleCollision(Circle &cir1, Circle &cir2){

    Vector2D vel1 = cir1.getVelocity();
    Vector2D vel2 = cir2.getVelocity();
    float mass1 = cir1.getMass();
    float mass2 = cir2.getMass();

    // momentum conservation
    Vector2D newVel1, newVel2;

    calcVelocitiesMomentumConservation(mass1, mass2, vel1.x, vel2.x, newVel1.x, newVel2.x);
    calcVelocitiesMomentumConservation(mass1, mass2, vel1.y, vel2.y, newVel1.y, newVel2.y);

    Point2D center1 = cir1.getCenter();
    Point2D center2 = cir2.getCenter();

    // find how much to shift
    float distNeeded = cir1.getRadius() + cir2.getRadius();
    Vector2D distActual = center1 - center2;
    float shift = distNeeded - distActual.length();

    // find normals
    Vector2D normal1 = center1 - center2;
    Vector2D normal2 = center2 - center1;
    normal1.normalize();
    normal2.normalize();

    // find shift vectors
    float coeffMultiplyVel1 = (shift / 2) / (newVel1.dot(normal1) * normal1).length();
    Vector2D shiftVector1 = coeffMultiplyVel1 * newVel1;
    float coeffMultiplyVel2 = (shift / 2) / (newVel2.dot(normal2) * normal2).length();
    Vector2D shiftVector2 = coeffMultiplyVel2 * newVel2;

    cir1.shift(shiftVector1);
    cir2.shift(shiftVector2);

    cir1.setVelocity(newVel1);
    cir2.setVelocity(newVel2);
}

void CollisionManager::resolveCircleRectCollision(Circle &obj1, Rect &obj2){

}

void CollisionManager::resolveRectRectCollision(Rect &obj1, Rect &obj2){

}

bool CollisionManager::checkCircleCircleIntersection(Circle &obj1, Circle &obj2)
{
    CircleCollisionShape* shape1 = dynamic_cast<CircleCollisionShape*>(obj1.getCollisionShape());
    CircleCollisionShape* shape2 = dynamic_cast<CircleCollisionShape*>(obj2.getCollisionShape());
    float distance = sqrt(pow(shape1->getPosition().x - shape2->getPosition().x , 2) 
    + pow(shape1->getPosition().y - shape2->getPosition().y , 2));

    if (distance < shape1->getRadius() + shape2->getRadius())
        return true;
    return false;
}

bool CollisionManager::checkCircleRectIntersection(Circle &obj1, Rect &obj2){
    CircleCollisionShape* shapeCir = dynamic_cast<CircleCollisionShape*>(obj1.getCollisionShape());
    RectCollisionShape* shapeRect = dynamic_cast<RectCollisionShape*>(obj2.getCollisionShape());

    Point2D posCir = shapeCir->getPosition();
    Point2D posRect = shapeRect->getPosition();
    float radius = shapeCir->getRadius();
    float rectWidth = shapeRect->getWidth();
    float rectHeight = shapeRect->getHeight();

    float distanceX = std::abs(posCir.x - posRect.x);
    float distanceY = std::abs(posCir.y - posRect.y);

    if (distanceX > (rectWidth / 2 + radius))
        return false;
    if (distanceY > (rectHeight / 2 + radius))
        return false;
    if (distanceX <= (rectWidth / 2))
        return true;
    if (distanceY <= (rectHeight / 2))
        return true;

    float squaredCornerDistance = pow((distanceX - rectWidth / 2), 2) + pow((distanceY - rectHeight / 2), 2);
    return (squaredCornerDistance <= pow(radius, 2));
}

void CollisionManager::addObject(CollidableObject *obj){
    collidableObjects.push_back(obj);
}

void CollisionManager::removeObject(CollidableObject *obj){
    collidableObjects.erase(std::remove(collidableObjects.begin(), collidableObjects.end(), obj), collidableObjects.end());
}

void CollisionManager::resolveCollisions(){
    for (int i = 0; i < collidableObjects.size(); i++){
        for (int j = i + 1; j < collidableObjects.size(); j++){
            CollidableObject* obj1 = collidableObjects[i];
            CollidableObject* obj2 = collidableObjects[j];

            // definetely no collision
            if (!checkAABBintersection(obj1->getCollisionShape()->getAABB(), obj2->getCollisionShape()->getAABB())){
                continue;
            }

            // check more calefully and resolve if needed    
            if (obj1->getObjectType() == ObjectType::RIGIDBODY && obj2->getObjectType() == ObjectType::RIGIDBODY){
                RigidBody* rig1 = (RigidBody*)obj1;
                RigidBody* rig2 = (RigidBody*)obj2;
                RigidBodyType rigType1 = rig1->getRigBodyType();
                RigidBodyType rigType2 = rig2->getRigBodyType();

                bool collided = false;

                if (rigType1 == RigidBodyType::CIRCLE && rigType2 == RigidBodyType::CIRCLE){
                    Circle* cir1 = (Circle*)rig1;
                    Circle* cir2 = (Circle*)rig2;
                    collided = checkCircleCircleIntersection(*cir1, *cir2);
                }
                else if (rigType1 == RigidBodyType::CIRCLE && rigType2 == RigidBodyType::RECT){
                    Circle* cir1 = (Circle*)rig1;
                    Rect* rect2 = (Rect*)rig2;
                    collided = checkCircleRectIntersection(*cir1, *rect2);
                }
                else if (rigType1 == RigidBodyType::RECT && rigType2 == RigidBodyType::RECT){
                    // As AABB intersect, rects definetely intersect
                    collided = true;
                }
                // TODO add else

                if (collided){
                    resolveRigidRigidCollision(*rig1, *rig2);
                }
                continue;
            }

            //TODO add softbody
        }
    }
}
