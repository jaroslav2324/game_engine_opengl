#include "CollisionManager.h"

// TODO move to AABB
bool CollisionManager::checkAABBintersection(const AABB &a, const AABB &b){

    if (a.x > b.x + b.w || a.x + a.w < b.x || a.y > b.y + b.h || a.y + a.h < b.y)
        return false;
    return true;
}

bool CollisionManager::checkSoftPointRectIntersection(SoftbodyPoint &point, Rect &rect){
    mathsCircle mCir = point.getMathsCircle();
    mathsRect mRect = rect.getMathsRect();
    return mCir.intersectsRect(mRect);
}

void CollisionManager::checkResolveSoftRectCollision(Softbody &soft, Rect &rect){
    for (auto& point: soft.getPoints()){
        if(checkSoftPointRectIntersection(point, rect)){
            Vector2D lineVec = getSoftPointRectIntersectionLineVec(point, rect);
            if (lineVec.isZeroVector()){
                Vector2D currVel = point.physicsParameters.velocityVec;
                lineVec.x = -currVel.y;
                lineVec.y = currVel.x;
            }
            Vector2D normal(-lineVec.y, lineVec.x);
            normal = normal.normalize();
            if (point.physicsParameters.velocityVec.dot(normal) > 0){
                normal = -normal;
            }
            pushSoftPointFromStaticRect(point, rect, normal);
            Vector2D newVel = reflectVelocityIfDirectsAgainstNormal(point.physicsParameters.velocityVec, normal);
            point.physicsParameters.velocityVec = newVel;
        }
    }   
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

void CollisionManager::pushCirclesApart(Circle &cir1, Circle &cir2){
    // // find how much to shift
    float distNeeded = cir1.getRadius() + cir2.getRadius();
    Vector2D distVec = cir1.getCenter() - cir2.getCenter();
    float shift = distNeeded - distVec.length();
    shift += 1e-3;

    //  find shift vectors
    Vector2D normal = distVec.normalize();
    Vector2D shiftVector1 = shift / 2 * normal;
    Vector2D shiftVector2 = -(shift / 2 * normal);

    cir1.shift(shiftVector1);
    cir2.shift(shiftVector2);
}

void CollisionManager::pushCirFromStaticCir(Circle &cir1, Circle &staticCir){
    Point2D center1 = cir1.getCenter();
    Point2D staticCenter = staticCir.getCenter();
    Vector2D normal = center1 - staticCenter;
    normal = normal.normalize();

    float distance = center1.distanceTo(staticCenter);
    float shift = cir1.getRadius() + staticCir.getRadius() - distance;
    Vector2D shiftVector = shift * normal;
    cir1.shift(shiftVector);
}

void CollisionManager::pushCirFromStaticRect(Circle & cir, Rect & rect, Vector2D shiftAlongNormal){
    // TODO change
    Vector2D shiftVec = shiftAlongNormal.normalize();
    do {
        cir.shift(shiftVec);
    } while(checkCircleRectIntersection(cir, rect));
}

void CollisionManager::pushSoftPointFromStaticRect(SoftbodyPoint &point, Rect &rect, Vector2D shiftAlongNormal){
    // TODO change
    Vector2D shiftVec = shiftAlongNormal.normalize();
    do {
        point.position.x += shiftVec.x;
        point.position.y += shiftVec.y;
    } while(checkSoftPointRectIntersection(point, rect));
}

void CollisionManager::pushSoftPointsApart(SoftbodyPoint& p1, SoftbodyPoint &p2){
    // // find how much to shift
    float distNeeded = p1.collisionShape.radius + p2.collisionShape.radius;
    Vector2D distVec = p1.position - p2.position;
    float shift = distNeeded - distVec.length();
    shift += 1e-3;

    //  find shift vectors
    Vector2D normal = distVec.normalize();
    Vector2D shiftVector1 = shift / 2 * normal;
    Vector2D shiftVector2 = -(shift / 2 * normal);

    p1.position.x += shiftVector1.x;
    p1.position.y += shiftVector1.y;
    p2.position.x += shiftVector2.x;
    p2.position.y += shiftVector2.y;
}

// reflects velocity of first body over velocity of second body 
// if velocity of first body directs in the opposite normal direction
// returns reflected(or not) velocity
Vector2D CollisionManager::reflectVelocityIfDirectsAgainstNormal(Vector2D vel, Vector2D normalReflectOver){
    if (vel.dot(normalReflectOver) < 0){
        return vel - 2 * vel.dot(normalReflectOver) * normalReflectOver;
    }
    else return vel;
}

bool CollisionManager::checkObjAABBintersect(CollidableObject& obj1, CollidableObject& obj2){
    ObjectType type1 = obj1.getObjectType();
    ObjectType type2 = obj2.getObjectType();

    AABB aabb1(0, 0, 0, 0);
    AABB aabb2(0, 0, 0, 0);

    if (type1 == ObjectType::RIGIDBODY){
        aabb1 = ((RigidBody&)obj1).getCollisionShape()->getAABB();
    }
    else if (type1 == ObjectType::SOFTBODY){
        aabb1 = ((Softbody&)obj1).getAABB();
    }
    if (type2 == ObjectType::RIGIDBODY){
        aabb2 = ((RigidBody&)obj2).getCollisionShape()->getAABB();
    }
    else if (type2 == ObjectType::SOFTBODY){
        aabb2 = ((Softbody&)obj2).getAABB();
    }

    return checkAABBintersection(aabb1, aabb2);
}

// simple velocity multiplication on elasticity coeff
void CollisionManager::applyCollisionEnergyLoss(RigidBody &body){
    if (body.isElastic()){
        float elCoeff = body.getElasticityCoeff();
        if (elCoeff < 1){
            body.setVelocity(body.getVelocity() * (elCoeff));
        }
    }
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
        Vector2D reflectedVel2 = reflectVelocityIfDirectsAgainstNormal(vel2, normal);

        pushCirFromStaticCir(cir2, cir1);
        applyCollisionEnergyLoss(cir2);
        cir2.setVelocity(reflectedVel2);

        return;
    }
    else if (cir2.isStatic()) {
        // reflect velocity of cir1
        Vector2D normal = center1 - center2;
        normal = normal.normalize();
        Vector2D reflectedVel1 = reflectVelocityIfDirectsAgainstNormal(vel1, normal);

        pushCirFromStaticCir(cir1, cir2);
        applyCollisionEnergyLoss(cir2);
        cir1.setVelocity(reflectedVel1);
        return;
    }

    float mass1 = cir1.getMass();
    float mass2 = cir2.getMass();

    Vector2D distVec = center1 - center2;

    Vector2D u1 = vel1 + (2 * mass2 * distVec / ((mass1 + mass2) * distVec.dot(distVec))) * (vel2 - vel1).dot(distVec);
    Vector2D u2 = vel2 - (2 * mass1 * distVec / ((mass1 + mass2) * distVec.dot(distVec))) * (vel2 - vel1).dot(distVec);

    pushCirclesApart(cir1, cir2);

    cir1.setVelocity(u1);
    cir2.setVelocity(u2);
}

// TODO Finish
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
        pushCirFromStaticRect(obj1, obj2, normal);
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

    // calcVelocitiesMomentumConservation(mass1, mass2, vel1.x, vel2.x, newVel1.x, newVel2.x);
    // calcVelocitiesMomentumConservation(mass1, mass2, vel1.y, vel2.y, newVel1.y, newVel2.y);

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

// TODO FInish
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

    // calcVelocitiesMomentumConservation(mass1, mass2, vel1.x, vel2.x, newVel1.x, newVel2.x);
    // calcVelocitiesMomentumConservation(mass1, mass2, vel1.y, vel2.y, newVel1.y, newVel2.y);

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

void CollisionManager::resolveSoftSoftCollision(Softbody &soft1, Softbody &soft2){
    for (auto& p1 : soft1.getPoints()){
        for (auto& p2: soft2.getPoints()){
            AABB aabb1 = p1.getCollShapeAABB();
            AABB aabb2 = p2.getCollShapeAABB();
            if (aabb1.intersects(aabb2)){
                resolveSoftPointSoftPointCollision(p1, p2);
            }
        }
    }
}

void CollisionManager::resolveSoftPointSoftPointCollision(SoftbodyPoint &p1, SoftbodyPoint &p2){
    float mass1 = p1.physicsParameters.mass;
    float mass2 = p2.physicsParameters.mass;

    Vector2D distVec = p1.position - p2.position;
    Vector2D vel1 = p1.physicsParameters.velocityVec;
    Vector2D vel2 = p2.physicsParameters.velocityVec;

    Vector2D u1 = vel1 + (2 * mass2 * distVec / ((mass1 + mass2) * distVec.dot(distVec))) * (vel2 - vel1).dot(distVec);
    Vector2D u2 = vel2 - (2 * mass1 * distVec / ((mass1 + mass2) * distVec.dot(distVec))) * (vel2 - vel1).dot(distVec);

    pushSoftPointsApart(p1, p2);

    p1.physicsParameters.velocityVec = vel1;
    p2.physicsParameters.velocityVec = vel2;
}

void CollisionManager::resolveSoftInnerCollisions(Softbody &obj){
    auto points = obj.getPoints();
    int amountPoints = points.size();
    for (int i = 0; i < amountPoints; i++){
        for (int j = 0; j < amountPoints; j++){
            if (i != j){
                AABB aabb1 = points[i].getCollShapeAABB();
                AABB aabb2 = points[j].getCollShapeAABB();
                if (aabb1.intersects(aabb2)){
                    pushSoftPointsApart(points[i], points[j]);
                }
            }
        }
    }

}

bool CollisionManager::checkRigRigIntersection(RigidBody &rig1, RigidBody &rig2){
    RigidBodyType rigType1 = rig1.getRigBodyType();
    RigidBodyType rigType2 = rig2.getRigBodyType();
    bool collided = false;

    if (rigType1 == RigidBodyType::CIRCLE && rigType2 == RigidBodyType::CIRCLE){
        collided = checkCircleCircleIntersection((Circle&)rig1, (Circle&)rig2);
    }
    else if (rigType1 == RigidBodyType::CIRCLE && rigType2 == RigidBodyType::RECT){
        collided = checkCircleRectIntersection((Circle&)rig1, (Rect&)rig2);
    }
    else if (rigType1 == RigidBodyType::RECT && rigType2 == RigidBodyType::CIRCLE){
        collided = checkCircleRectIntersection((Circle&)rig2, (Rect&)rig1);
    }
    else if (rigType1 == RigidBodyType::RECT && rigType2 == RigidBodyType::RECT){
        // As AABB intersect, rects definetely intersect
        collided = true;
    }
    else{
        std::cout << "ERROR: no option for rigid bodies collision check" << std::endl;
    }

    return collided;
}

bool CollisionManager::checkCircleCircleIntersection(Circle &obj1, Circle &obj2)
{
    CircleCollisionShape* shape1 = dynamic_cast<CircleCollisionShape*>(obj1.getCollisionShape());
    CircleCollisionShape* shape2 = dynamic_cast<CircleCollisionShape*>(obj2.getCollisionShape());
    mathsCircle mc1 = shape1->getMathsCircle();
    mathsCircle mc2 = shape2->getMathsCircle();
    return mc1.intersectsCircle(mc2);
}

bool CollisionManager::checkCircleRectIntersection(Circle &obj1, Rect &obj2){
    CircleCollisionShape* shapeCir = dynamic_cast<CircleCollisionShape*>(obj1.getCollisionShape());
    RectCollisionShape* shapeRect = dynamic_cast<RectCollisionShape*>(obj2.getCollisionShape());

    mathsCircle mCir = shapeCir->getMathsCircle();
    mathsRect mRect = shapeRect->getMathsRect();
    return mCir.intersectsRect(mRect);
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
            if (!checkObjAABBintersect(*obj1, *obj2)){
                continue;
            }

            // check more calefully and resolve if needed    
            if (obj1->getObjectType() == ObjectType::RIGIDBODY && obj2->getObjectType() == ObjectType::RIGIDBODY){
                RigidBody* rig1 = (RigidBody*)obj1;
                RigidBody* rig2 = (RigidBody*)obj2;

                if (rig1->isStatic() && rig2->isStatic()){
                    continue;
                }

                bool collided = checkRigRigIntersection(*rig1, *rig2);

                if (collided){
                    resolveRigidRigidCollision(*rig1, *rig2);
                    rig1->callOnCollisionCallback();
                    rig2->callOnCollisionCallback();
                }
                continue;
            }
            // one soft, one rigid
            if (obj1->getObjectType() == ObjectType::SOFTBODY && obj2->getObjectType() == ObjectType::RIGIDBODY ||
            obj1->getObjectType() == ObjectType::RIGIDBODY && obj2->getObjectType() == ObjectType::SOFTBODY){
                Softbody* soft;
                RigidBody* rigid;
                if (obj1->getObjectType() == ObjectType::SOFTBODY){
                    soft = (Softbody*)obj1;
                    rigid = (RigidBody*)obj2;
                }
                else{
                    soft = (Softbody*)obj2;
                    rigid = (RigidBody*)obj1;
                }

                if (rigid->getRigBodyType() == RigidBodyType::RECT){
                    checkResolveSoftRectCollision(*soft, (Rect&)*rigid);                         
                }

                continue;
            }

            if (obj1->getObjectType() == ObjectType::SOFTBODY && obj2->getObjectType() == ObjectType::SOFTBODY){

                resolveSoftSoftCollision((Softbody&)*obj1, (Softbody&)*obj2);
                continue;
            }
        }
    }

    // resolve inner colliisons for softbodies{
    for (auto& obj :collidableObjects){
        if (obj->getObjectType() == ObjectType::SOFTBODY){
            resolveSoftInnerCollisions((Softbody&) *obj);
        }
    }
}

Vector2D CollisionManager::getCircleRectIntersectionLineVec(Circle &cir, Rect &rect){
    mathsCircle mCir = cir.getMathsCircle();
    mathsRect mRect = rect.getMathsRect();
    return mRect.getIntersectionLineVecCircle(mCir);
}

Vector2D CollisionManager::getRectRectIntersectionLineVec(Rect& rect1, Rect& rect2){
    mathsRect mRect1 = rect1.getMathsRect();
    mathsRect mRect2 = rect2.getMathsRect();
    return mRect1.getIntersectionLineVecRect(mRect2);
}

Vector2D CollisionManager::getSoftPointRectIntersectionLineVec(SoftbodyPoint &point, Rect &rect){
    mathsCircle mCir = point.getMathsCircle();
    mathsRect mRect = rect.getMathsRect();
    return mRect.getIntersectionLineVecCircle(mCir);
}
