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

    // std::cout << "Circle Circle Collision" << std::endl;

    Vector2D vel1 = cir1.getVelocity();
    Vector2D vel2 = cir2.getVelocity();
    Point2D center1 = cir1.getCenter();
    Point2D center2 = cir2.getCenter();

    if (cir1.isStatic()){
        // reflect velocity of cir2
        Vector2D normal = center2 - center1;
        normal = normal.normalize();
        Vector2D reflectedVel2 = vel2 - 2 * vel2.dot(normal) * normal;

        // move cir 2 out of cir 1
        float distance = center2.distanceTo(center1);
        float shift = cir1.getRadius() + cir2.getRadius() - distance;
        Vector2D normReflVel2 = reflectedVel2.normalize();
        Vector2D shiftVector = shift * normReflVel2;
        cir2.shift(shiftVector);

        if (cir2.isElastic()){
            float elCoeff = cir2.getElasticityCoeff();
            if (elCoeff < 1){
                reflectedVel2 += vel2.project(normal) * (1 - elCoeff);
            }
        }
        cir2.setVelocity(reflectedVel2);

        return;
    }
    else if (cir2.isStatic()) {
        // reflect velocity of cir1
        Vector2D normal = center1 - center2;
        normal = normal.normalize();
        Vector2D reflectedVel1 = vel1 - 2 * vel1.dot(normal) * normal;

        // move cir 1 out of cir 2
        float distance = center1.distanceTo(center2);
        float shift = cir1.getRadius() + cir2.getRadius() - distance;
        Vector2D normReflVrl1 = reflectedVel1.normalize();
        Vector2D shiftVector = shift * normReflVrl1;
        cir1.shift(shiftVector);

        if (cir1.isElastic()){
            float elCoeff = cir1.getElasticityCoeff();
            if (elCoeff < 1){
                reflectedVel1 += vel1.project(normal) * (1 - elCoeff);
            }
        }
        cir1.setVelocity(reflectedVel1);
        return;
    }

    float mass1 = cir1.getMass();
    float mass2 = cir2.getMass();

    // points in direction of cir1
    Vector2D normal1 = center1 - center2;
    normal1 = normal1.normalize();
    // opposite directon
    Vector2D normal2 = -normal1;

    // reflect vectors
    Vector2D reflectedVel1 = vel1 - 2 * vel1.dot(normal1) * normal1;
    Vector2D reflectedVel2 = vel2 - 2 * vel2.dot(normal2) * normal2;

    float sumLength = reflectedVel1.length() + reflectedVel2.length();
    float sumMass = mass1 + mass2;

    float newLength1 = mass2 / sumMass * sumLength;
    float newLength2 = mass1 / sumMass * sumLength;

    if (!reflectedVel1.isZeroVector()){
        float mulCoeff1 = newLength1 / reflectedVel1.length();
        reflectedVel1 *= mulCoeff1;
    }
    else{
        reflectedVel1 = normal1 * newLength1;
    }
    if (!reflectedVel2.isZeroVector()){
        float mulCoeff2 = newLength2 / reflectedVel2.length();
        reflectedVel2 *= mulCoeff2;
    }
    else{
        reflectedVel2 = normal2 * newLength2;
    }

    // // find how much to shift
    float distNeeded = cir1.getRadius() + cir2.getRadius();
    Vector2D distActual = center1 - center2;
    float shift = distNeeded - distActual.length();
    shift += 1e-3;

    // // find shift vectors
    float coeffMultiplyVel1 = (shift / 2) / reflectedVel1.project(normal1).length();
    Vector2D shiftVector1 = coeffMultiplyVel1 * reflectedVel1;
    float coeffMultiplyVel2 = (shift / 2) / reflectedVel2.project(normal2).length();
    Vector2D shiftVector2 = coeffMultiplyVel2 * reflectedVel2;

    cir1.shift(shiftVector1);
    cir2.shift(shiftVector2);

    if (cir1.isElastic()){
        float elCoeff = cir1.getElasticityCoeff();
        if (elCoeff < 1){
            reflectedVel1 += vel1.project(normal1) * (1 - elCoeff);
        }
    }
    if (cir2.isElastic()){
        float elCoeff = cir2.getElasticityCoeff();
        if (elCoeff < 1){
            reflectedVel2 += vel2.project(normal2) * (1 - elCoeff);
        }
    }

    cir1.setVelocity(reflectedVel1);
    cir2.setVelocity(reflectedVel2);
}

void CollisionManager::resolveCircleRectCollision(Circle &obj1, Rect &obj2){

    // std::cout << "CircleRectCollision" << std::endl;

    Vector2D vel1 = obj1.getVelocity();
    Vector2D vel2 = obj2.getVelocity();

    if (obj1.isStatic()){
        // reflect velocity of rect
        // get intersection line vector
        Vector2D lineVec = getCircleRectIntersectionLineVec(obj1, obj2);
        Vector2D normal(-lineVec.y, lineVec.x);
        // normal must direct from circle
        if (vel2.dot(normal) > 0){
            normal = -normal;
        }
        normal = normal.normalize();
        Vector2D reflectedVel = vel2 - 2 * vel2.dot(normal) * normal;
        // move cir out of rect
        // TODO change
        int shiftVal = 1;
        Vector2D normedVel = reflectedVel;
        normedVel = normedVel.normalize();
        while(checkCircleRectIntersection(obj1, obj2)){
            obj2.shift(shiftVal * normedVel);
        }
        if (obj2.isElastic()){
            float elCoeff = obj2.getElasticityCoeff();
            if (elCoeff < 1){
                reflectedVel += vel2.project(normal) * (1 - elCoeff);
            }
        }
        obj2.setVelocity(reflectedVel);
        return;
    }

    if (obj2.isStatic()){
        // reflect velocity of circle
        // get intersection line vector
        Vector2D lineVec = getCircleRectIntersectionLineVec(obj1, obj2);
        Vector2D normal(-lineVec.y, lineVec.x);
        // normal must direct from rect
        if (vel1.dot(normal) > 0){
            normal = -normal;
        }
        normal = normal.normalize();
        Vector2D reflectedVel = vel1 - 2 * vel1.dot(normal) * normal;
        // move rect out of cir
        // TODO change
        int shiftVal = 1;
        Vector2D normedVel = reflectedVel;
        normedVel = normedVel.normalize();
        while(checkCircleRectIntersection(obj1, obj2)){
            obj1.shift(shiftVal * normedVel);
        }
        if (obj1.isElastic()){
            float elCoeff = obj1.getElasticityCoeff();
            if (elCoeff < 1){
                reflectedVel += vel1.project(normal) * (1 - elCoeff);
            }
        }
        obj1.setVelocity(reflectedVel);
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

    // std::cout << "RectRectCollision" << std::endl;

    Vector2D vel1 = obj1.getVelocity();
    Vector2D vel2 = obj2.getVelocity();

    if (obj1.isStatic()){
        // reflect velocity of rect2
        // get intersection line vector
        Vector2D lineVec = getRectRectIntersectionLineVec(obj1, obj2);
        Vector2D normal(-lineVec.y, lineVec.x);
        // normal must direct from rect1
        if (vel2.dot(normal) > 0){
            normal = -normal;
        }
        normal = normal.normalize();
        Vector2D reflectedVel = vel2 - 2 * vel2.dot(normal) * normal;
        obj2.setVelocity(reflectedVel);
        // move rect2 out of rect1
        // TODO change
        int shiftVal = 1;
        Vector2D normedVel = reflectedVel;
        normedVel = normedVel.normalize();
        while(checkAABBintersection(obj1.getCollisionShape()->getAABB(), obj2.getCollisionShape()->getAABB())){
            obj2.shift(shiftVal * normedVel);
        }
        return;
    }

    if (obj2.isStatic()){
        // reflect velocity of rect1
        // get intersection line vector
        Vector2D lineVec = getRectRectIntersectionLineVec(obj1, obj2);
        Vector2D normal(-lineVec.y, lineVec.x);
        // normal must direct from rect1
        if (vel1.dot(normal) > 0){
            normal = -normal;
        }
        normal = normal.normalize();
        Vector2D reflectedVel = vel1 - 2 * vel1.dot(normal) * normal;
        obj1.setVelocity(reflectedVel);
        // move rect2 out of rect1
        // TODO change
        int shiftVal = 1;
        Vector2D normedVel = reflectedVel;
        normedVel = normedVel.normalize();
        while(checkAABBintersection(obj1.getCollisionShape()->getAABB(), obj2.getCollisionShape()->getAABB())){
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
Vector2D CollisionManager::getCircleRectIntersectionLineVec(Circle &cir, Rect &rect){
    float radius = cir.getRadius();
    float cx = cir.getCenter().x;
    float cy = cir.getCenter().y;

    // create segments
    Point2D segsP1[4];
    Point2D segsP2[4];
    fillRectSegments(rect.getCenter(), rect.getWidth(), rect.getHeight(), segsP1, segsP2);

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

void CollisionManager::fillRectSegments(Point2D center, float width, float height, Point2D *segsX, Point2D* segsY){
    segsX[0] = Point2D(center.x - width/2, center.y - height/2);
    segsY[1] = Point2D(center.x + width/2, center.y + height/2);
    segsX[2] = Point2D(center.x + width/2, center.y + height/2);
    segsY[0] = Point2D(center.x + width/2, center.y - height/2);
    segsY[2] = Point2D(center.x - width/2, center.y + height/2);
    segsX[3] = Point2D(center.x - width/2, center.y + height/2);
    segsX[1] = Point2D(center.x + width/2, center.y - height/2);
    segsY[3] = Point2D(center.x - width/2, center.y - height/2);
}

//TODO refactor
int CollisionManager::findSegmentSegmentIntersection(Point2D seg1P1, Point2D seg1P2,   
                                    Point2D seg2P1, Point2D seg2P2,   
                                    Point2D& intersectionP1){
    Point2D intP;
    Vector2D vecDirection1(seg1P1.x - seg1P2.x, seg1P1.y - seg1P2.y);
    Vector2D vecDirection2(seg2P1.x - seg2P2.x, seg2P1.y - seg2P2.y);

    // lines are parallel
    if (std::abs(vecDirection1.dot(vecDirection2) - vecDirection1.length() * vecDirection2.length()) < 1e-6){
        // TODO check collinear vectors
        return 0;
    }            

    //TODO refactor this
    float n;
    if (seg1P2.y - seg1P1.y != 0) {  
        float q = (seg1P2.x - seg1P1.x) / (seg1P1.y - seg1P2.y);   
        float sn = (seg2P1.x - seg2P2.x) + (seg2P1.y - seg2P2.y) * q; 
        if (!sn) { 
            // lines do not intersect
            return 0;
        } 
        else{
            float fn = (seg2P1.x - seg1P1.x) + (seg2P1.y - seg1P1.y) * q;   
            n = fn / sn;
        }
    }
    else {
        if (!(seg2P1.x - seg2P2.x)) { 
            // lines do not intersect
            return 0;
        }  
        else{
            n = (seg2P1.y - seg1P1.y) / (seg2P1.y - seg2P2.y);
        }  
    }
    intP.x = seg2P1.x + (seg2P2.x - seg2P1.x) * n;  
    intP.y = seg2P1.y + (seg2P2.y - seg2P1.y) * n;  

    if ( pointOnSegment(intP, seg1P1, seg1P2) && pointOnSegment(intP, seg2P1, seg2P2)){
        intersectionP1 = intP;
        return 1;
    }
    return 0;
}

Vector2D CollisionManager::getRectRectIntersectionLineVec(Rect& rect1, Rect& rect2){

    // create segments
    Point2D segs1P1[4];
    Point2D segs1P2[4];
    fillRectSegments(rect1.getCenter(), rect1.getWidth(), rect1.getHeight(), segs1P1, segs1P2);
    Point2D segs2P1[4];
    Point2D segs2P2[4];
    fillRectSegments(rect2.getCenter(), rect2.getWidth(), rect2.getHeight(), segs2P1, segs2P2);

    int countInterPoints = 0;
    Point2D interPoints[16];
    int currInterPidx = 0;
    Point2D interP;
    for (int idx1 = 0; idx1 < 4; idx1++){
        for (int idx2 = idx1 + 1; idx2 < 4; idx2++){
            int count = findSegmentSegmentIntersection(segs1P1[idx1], segs1P2[idx1], segs2P1[idx2], segs2P2[idx2], interP);
            if (count == 1){
                interPoints[currInterPidx] = interP;
                currInterPidx++;
                countInterPoints += count;
            }
        }
    }
    if (countInterPoints < 1 || countInterPoints > 2){
        std::cout << "ERROR: Rect Rect intersection points wrong count: " << countInterPoints << "\n";
    }

    return Vector2D(interPoints[0].x - interPoints[1].x, interPoints[0].y - interPoints[1].y);
}