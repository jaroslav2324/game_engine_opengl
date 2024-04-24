#include "randomGeneration.h"

float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

std::vector<Point2D> generateRandomPoints(int numPoints, Point2D center, float minShiftX, float maxShiftX, float minShiftY, float maxShiftY) {
    
    std::vector<Point2D> randomPoints;
    Point2D tempPoint;

    for (int i = 0; i < numPoints; ++i) {
        tempPoint.x = center.x + randomFloat(minShiftX, maxShiftX);
        tempPoint.y = center.y + randomFloat(minShiftY, maxShiftY);
        randomPoints.push_back(tempPoint);
    }

    return randomPoints;
}