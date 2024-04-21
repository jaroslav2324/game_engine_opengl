#include "circle.h"

//TODO remove
float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

//TODO remove
std::vector<Point2D> generateRandomPoints(int numPoints, Point2D center, float minX, float maxX, float minY, float maxY) {
    
    std::vector<Point2D> randomPoints;
    Point2D tempPoint;

    for (int i = 0; i < numPoints; ++i) {
        tempPoint.x = center.x + randomFloat(minX, maxX);
        tempPoint.y = center.y + randomFloat(minY, maxY);
        randomPoints.push_back(tempPoint);
    }

    return randomPoints;
}

Circle::Circle(Renderer* renderer, Point2D center){

    this->center = center;
    auto points = generateRandomPoints(10, center, -100, 100, -100, 100);
    renderedTriangles = triangulateBowyerWatson(points);
}

std::vector<NodesEdgesTriangles> &Circle::getRenderedTriangles(){
    return renderedTriangles;
}
