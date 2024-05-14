#include "SoftbodyCircle.h"

SoftbodyCircle::SoftbodyCircle(Point2D center, float radius, int numPoints)
: Softbody(SoftbodyType::SOFTBODY_CIRCLE){
    this->radius = radius;
    auto points2D = generateCirclePoints(center, radius, numPoints);
    for (auto& p: points2D){
        this->points.push_back(p);
    }
    points.push_back(center);
    
    // TODO change
    float tempStiffness = 10.0f;
    float tempDamping = 0.1f;

    float distBetweenPoints = points2D[0].distanceTo(points2D[1]); 
    for (int i = 0; i < numPoints - 1; i++){
        this->springs.push_back(SoftbodySpring(&points[i], &points[i + 1], distBetweenPoints, tempStiffness, tempDamping));
    }
    this->springs.push_back(SoftbodySpring(&points[numPoints - 1], &points[0], distBetweenPoints, tempStiffness, tempDamping));

    // for (int i = 0; i < numPoints; i++){
    //     this->springs.push_back(SoftbodySpring(&points[i], &points[(i + numPoints / 2) % numPoints], 2 * radius, tempStiffness, tempDamping));
    // }

    for (int i = 0; i < numPoints; i++){
        this->springs.push_back(SoftbodySpring(&points[i], &points[numPoints], radius, tempStiffness, tempDamping));
    }
}

float SoftbodyCircle::getRadius(){
    return radius;
}
