#include "pointsGeneration.h"

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

std::vector<Point2D> generateCirclePoints(Point2D center, float radius, int num_points){
    std::vector<Point2D> points;
    float angle_increment = 2 * M_PI / num_points;

    for (int i = 0; i < num_points; ++i) {
        float angle = i * angle_increment;
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        points.push_back(Point2D(x, y));
    }

    return points;
}
