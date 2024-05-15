#include "SoftbodyCell.h"

SoftbodyCell::SoftbodyCell(Point2D center, float radius)
:Softbody(SoftbodyType::SOFTBODY_CELL){
    this->outerRadius = radius;
    this->innerRadius = radius / 2;

    float firstNeighbourStiffness = 10.0f;
    float secondNeighbourStiffness = 3.0f;
    float stiffnessBetweenRadiuses = 20.0f;
    

    SoftbodyPoint defaultPoint({0, 0});

    int numOuterPoints = 0.8 * (2 * M_PI * outerRadius / (2 * defaultPoint.collisionShape.radius));
    int numInnerPoints = numOuterPoints / 2;

    auto outerPoints = generateCirclePoints(center, outerRadius, numOuterPoints);
    auto innerPoints = generateCirclePoints(center, innerRadius, numInnerPoints);

    points.reserve(numInnerPoints + numOuterPoints);

    for (auto& op: outerPoints){
        points.push_back(op);
    }

    for (auto& ip: innerPoints){
        points.push_back(ip);
    }

    // form outer spring radius
    float outerRestLen = outerPoints[0].distanceTo(outerPoints[1]);
    float outerRestLenDoubled = outerRestLen * 2;
    for (int i= 0; i < numOuterPoints; i++){
        int idxMin2 = (i - 2 + numOuterPoints) % numOuterPoints;
        int idxMin1 = (idxMin2 + 1) % numOuterPoints;
        int idx = (idxMin2 + 2) % numOuterPoints;
        int idxPlus1 = (idxMin2 + 3) % numOuterPoints;
        int idxPlus2 = (idxMin2 + 4) % numOuterPoints;
        springs.push_back(SoftbodySpring(&points[idxMin2], &points[idx], outerRestLenDoubled, secondNeighbourStiffness, 0.1f));
        springs.push_back(SoftbodySpring(&points[idxMin1], &points[idx], outerRestLen, firstNeighbourStiffness, 0.1f));
        springs.push_back(SoftbodySpring(&points[idxPlus1], &points[idx], outerRestLen, firstNeighbourStiffness, 0.1f));
        springs.push_back(SoftbodySpring(&points[idxPlus2], &points[idx], outerRestLenDoubled, secondNeighbourStiffness, 0.1f));
    }

    // form inner radius
    float innerRestLen = innerPoints[0].distanceTo(innerPoints[1]);
    float innerRestLenDoubled = innerRestLen * 2;
    for (int i= 0; i < numInnerPoints; i++){
        int idxMin2 = (i - 2 + numInnerPoints) % numInnerPoints + numOuterPoints;
        int idxMin1 = (i - 1 + numInnerPoints) % numInnerPoints + numOuterPoints;
        int idx = (i + numInnerPoints) % numInnerPoints + numOuterPoints;
        int idxPlus1 = (i + 1 + numInnerPoints) % numInnerPoints + numOuterPoints;
        int idxPlus2 = (i + 2 + numInnerPoints) % numInnerPoints + numOuterPoints;
        springs.push_back(SoftbodySpring(&points[idxMin2], &points[idx], innerRestLenDoubled, secondNeighbourStiffness, 0.1f));
        springs.push_back(SoftbodySpring(&points[idxMin1], &points[idx], innerRestLen, firstNeighbourStiffness, 0.1f));
        springs.push_back(SoftbodySpring(&points[idxPlus1], &points[idx], innerRestLen, firstNeighbourStiffness, 0.1f));
        springs.push_back(SoftbodySpring(&points[idxPlus2], &points[idx], innerRestLenDoubled, secondNeighbourStiffness, 0.1f));
    } 

    float distanceBetweenRadiuses = outerRadius - innerRadius;
    // connect radiuses
    for (int i = 0; i < numInnerPoints; i++){
        int idxInner = i + numOuterPoints;
        int idxOuter = 2 * i;
        springs.push_back(SoftbodySpring(&points[idxInner], &points[idxOuter], distanceBetweenRadiuses, stiffnessBetweenRadiuses, 0.1f));
    }
}