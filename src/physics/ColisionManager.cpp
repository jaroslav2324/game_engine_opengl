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
    else if (rigType1 == RigidBodyType::RECT && rigType2 == RigidBodyType::CIRCLE){
        resolveCircleRectCollision((Circle&)obj2, (Rect&)obj1); 
    }
    else if (rigType1 == RigidBodyType::RECT && rigType2 == RigidBodyType::RECT){
        resolveRectRectCollision((Rect&)obj1, (Rect&)obj2);
    }
    // TODO: add UNDEFINED handling
}

void CollisionManager::resolveCircleCircleCollision(Circle &cir1, Circle &cir2){

    std::cout << "Circle Circle Collision" << std::endl;

    Vector2D vel1 = cir1.getVelocity();
    Vector2D vel2 = cir2.getVelocity();

    if (cir1.isStatic()){
        // reflect velocity of cir 1
        Vector2D normal = cir2.getCenter() - cir1.getCenter();
        normal.normalize();
        Vector2D reflectedVel2 = vel2 - 2 * vel2.dot(normal) * normal;
        cir2.setVelocity(reflectedVel2);
        // move cir 2 out of cir 1
        float distance = sqrt(pow(cir1.getCenter().x - cir2.getCenter().x, 2) + pow(cir1.getCenter().y - cir2.getCenter().y, 2));
        float shift = cir1.getRadius() + cir2.getRadius() - distance;
        Vector2D shiftVector = shift * reflectedVel2.normalize();
        cir2.shift(shiftVector);
        return;
    }
    else if (cir2.isStatic()) {
        // reflect velocity of cir 2
        Vector2D normal = cir1.getCenter() - cir2.getCenter();
        normal.normalize();
        Vector2D reflectedVel1 = vel1 - 2 * vel1.dot(normal) * normal;
        cir1.setVelocity(reflectedVel1);
        // move cir 1 out of cir 2
        float distance = sqrt(pow(cir1.getCenter().x - cir2.getCenter().x, 2) + pow(cir1.getCenter().y - cir2.getCenter().y, 2));
        float shift = cir1.getRadius() + cir2.getRadius() - distance;
        Vector2D shiftVector = shift * reflectedVel1.normalize();
        cir1.shift(shiftVector);
        return;
    }

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

    std::cout << "CircleRectCollision" << std::endl;

    Vector2D vel1 = obj1.getVelocity();
    Vector2D vel2 = obj2.getVelocity();

    if (obj1.isStatic()){
        // reflect velocity of rect
        // get intersection line vector
        Vector2D lineVec = gecCircleRectIntersectionLineVec(obj1, obj2);
        Vector2D normal(-lineVec.y, lineVec.x);
        // normal must direct from circle
        if (vel2.dot(normal) > 0){
            normal = -normal;
        }
        normal.normalize();
        Vector2D reflectedVel = vel2 - 2 * vel2.dot(normal) * normal;
        obj2.setVelocity(reflectedVel);
        // move cir out of rect
        // TODO change
        int shiftVal = 1;
        Vector2D normedVel = reflectedVel;
        normedVel.normalize();
        while(checkCircleRectIntersection(obj1, obj2)){
            obj2.shift(shiftVal * normedVel);
        }
        return;
    }

    if (obj2.isStatic()){
        // reflect velocity of circle
        // get intersection line vector
        Vector2D lineVec = gecCircleRectIntersectionLineVec(obj1, obj2);
        Vector2D normal(-lineVec.y, lineVec.x);
        // normal must direct from rect
        if (vel1.dot(normal) > 0){
            normal = -normal;
        }
        normal.normalize();
        Vector2D reflectedVel = vel1 - 2 * vel1.dot(normal) * normal;
        obj1.setVelocity(reflectedVel);
        // move rect out of cir
        // TODO change
        int shiftVal = 1;
        Vector2D normedVel = reflectedVel;
        normedVel.normalize();
        while(checkCircleRectIntersection(obj1, obj2)){
            obj1.shift(shiftVal * normedVel);
        }
        return;
    }

    float mass1 = obj1.getMass();
    float mass2 = obj2.getMass();

    // momentum conservation
    Vector2D newVel1, newVel2;

    calcVelocitiesMomentumConservation(mass1, mass2, vel1.x, vel2.x, newVel1.x, newVel2.x);
    calcVelocitiesMomentumConservation(mass1, mass2, vel1.y, vel2.y, newVel1.y, newVel2.y);

    Point2D center1 = obj1.getCenter();
    Point2D center2 = obj2.getCenter();

    Vector2D normalizedNewVel1 = Vector2D(newVel1).normalize();
    Vector2D normalizedNewVel2 = Vector2D(newVel2).normalize();

    if (normalizedNewVel1.isZeroVector() && normalizedNewVel2.isZeroVector()){
        normalizedNewVel1 = Vector2D(1, 0);
        normalizedNewVel2 = Vector2D(-1, 0);
    }

    //TODO change algorithm
    // iteratively shift
    while (checkAABBintersection(obj1.getCollisionShape()->getAABB(), obj2.getCollisionShape()->getAABB())){
        obj1.shift(normalizedNewVel1);
        obj2.shift(normalizedNewVel2);
        normalizedNewVel1 *= 2;
        normalizedNewVel2 *= 2;
    }
    
    obj1.setVelocity(newVel1);
    obj2.setVelocity(newVel2);
}

void CollisionManager::resolveRectRectCollision(Rect &obj1, Rect &obj2){

    std::cout << "RectRectCollision" << std::endl;

    Vector2D vel1 = obj1.getVelocity();
    Vector2D vel2 = obj2.getVelocity();
    float mass1 = obj1.getMass();
    float mass2 = obj2.getMass();

    // momentum conservation
    Vector2D newVel1, newVel2;

    calcVelocitiesMomentumConservation(mass1, mass2, vel1.x, vel2.x, newVel1.x, newVel2.x);
    calcVelocitiesMomentumConservation(mass1, mass2, vel1.y, vel2.y, newVel1.y, newVel2.y);

    Point2D center1 = obj1.getCenter();
    Point2D center2 = obj2.getCenter();

    Vector2D normalizedNewVel1 = Vector2D(newVel1).normalize();
    Vector2D normalizedNewVel2 = Vector2D(newVel2).normalize();

    if (normalizedNewVel1.isZeroVector() && normalizedNewVel2.isZeroVector()){
        normalizedNewVel1 = Vector2D(1, 0);
        normalizedNewVel2 = Vector2D(-1, 0);
    }

    //TODO change algorithm
    // iteratively shift
    while (checkAABBintersection(obj1.getCollisionShape()->getAABB(), obj2.getCollisionShape()->getAABB())){
        obj1.shift(normalizedNewVel1);
        obj2.shift(normalizedNewVel2);
        normalizedNewVel1 *= 2;
        normalizedNewVel2 *= 2;
    }
    
    obj1.setVelocity(newVel1);
    obj2.setVelocity(newVel2);
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

                if (rig1->isStatic() && rig2->isStatic()){
                    continue;
                }

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
                else if (rigType1 == RigidBodyType::RECT && rigType2 == RigidBodyType::CIRCLE){
                    Rect* rect1 = (Rect*)rig1;
                    Circle* cir2 = (Circle*)rig2;
                    collided = checkCircleRectIntersection(*cir2, *rect1);
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

bool CollisionManager::pointOnSegment(Point2D point, Point2D segP1, Point2D segP2){
    float AB = sqrt((segP2.x-segP1.x)*(segP2.x-segP1.x)+(segP2.y-segP1.y)*(segP2.y-segP1.y));
    float AP = sqrt((point.x-segP1.x)*(point.x-segP1.x)+(point.y-segP1.y)*(point.y-segP1.y));
    float PB = sqrt((segP2.x-point.x)*(segP2.x-point.x)+(segP2.y-point.y)*(segP2.y-point.y));
    if(AB - (AP + PB) < 1e-6)
        return true;
    return false;
}

// Find the points of segment-circle intersection
int CollisionManager::FindSegmentCircleIntersections(float cx, float cy, float radius,
                                        Point2D segP1, Point2D segP2,                
                                        Point2D& intersectionP1,  Point2D& intersectionP2)
{
    float dx, dy, A, B, C, det, t;

    dx = segP2.x - segP1.x;
    dy = segP2.y - segP1.y;

    A = dx * dx + dy * dy;
    B = 2 * (dx * (segP1.x - cx) + dy * (segP1.y - cy));
    C = (segP1.x - cx) * (segP1.x - cx) + (segP1.y - cy) * (segP1.y - cy) - radius * radius;

    det = B * B - 4 * A * C;
    if ((A <= 0.000001) || (det < 0)){
        return 0;
    }
    else if (det == 0){
        // One solution.
        t = -B / (2 * A);
        Point2D int1(segP1.x + t * dx, segP1.y + t * dy);
        if (pointOnSegment(int1, segP1, segP2)){
            intersectionP1 = int1;
            return 1;
        }
        return 0;
    }
    else
    {
        // Two solutions.
        t = (float)((-B + sqrt(det)) / (2 * A));
        Point2D int1(segP1.x + t * dx, segP1.y + t * dy);
        t = (float)((-B - sqrt(det)) / (2 * A));
        Point2D int2(segP1.x + t * dx, segP1.y + t * dy);
        bool int1OnSeg = pointOnSegment(int1, segP1, segP2);
        bool int2OnSeg = pointOnSegment(int2, segP1, segP2);

        if (int1OnSeg && !int2OnSeg){
            intersectionP1 = int1;
            return 1;
        }
        if (!int1OnSeg && int2OnSeg){
            intersectionP1 = int2;
            return 1;
        }
        if (int1OnSeg && int2OnSeg){
            intersectionP1 = int1;
            intersectionP2 = int2;
            return 2;
        }

        return 0;
    }
}

// TODO REFACTOR
Vector2D CollisionManager::gecCircleRectIntersectionLineVec(Circle &cir, Rect &rect){
    float radius = cir.getRadius();
    float cx = cir.getCenter().x;
    float cy = cir.getCenter().y;
    float rx = rect.getCenter().x;
    float ry = rect.getCenter().y;
    float rw = rect.getWidth();
    float rh = rect.getHeight();

    // create segments
    Point2D segsP1[4];
    Point2D segsP2[4];
    segsP1[0] = Point2D(rx - rw/2, ry - rh/2);
    segsP2[0] = Point2D(rx + rw/2, ry - rh/2);
    segsP1[1] = Point2D(rx + rw/2, ry - rh/2);
    segsP2[1] = Point2D(rx + rw/2, ry + rh/2);
    segsP1[2] = Point2D(rx + rw/2, ry + rh/2);
    segsP2[2] = Point2D(rx - rw/2, ry + rh/2);
    segsP1[3] = Point2D(rx - rw/2, ry + rh/2);
    segsP2[3] = Point2D(rx - rw/2, ry - rh/2);

    int countInters = 0;
    Point2D inters[8];
    int idxCurrEmptyInter = 0;
    Point2D inter1;
    Point2D inter2;
    for (int segIdx = 0; segIdx < 4; segIdx++){
        int count = FindSegmentCircleIntersections(cx, cy, radius, segsP1[segIdx], segsP2[segIdx], inter1, inter2);
        if (count == 2){
            inters[idxCurrEmptyInter] = inter1;
            idxCurrEmptyInter++;
            inters[idxCurrEmptyInter] = inter2;
            idxCurrEmptyInter++;
        }
        if (count == 1){
            inters[idxCurrEmptyInter] = inter1;
            idxCurrEmptyInter++;
        }
        countInters += count;
    }
    if (countInters < 1 || countInters > 2){
        std::cout << "ERROR: amount intersections of rect and circle is " << countInters << "\n";
    }

    return Vector2D(inter1.x - inter2.x, inter1.y - inter2.y);
}
