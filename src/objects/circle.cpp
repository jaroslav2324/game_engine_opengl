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

std::vector<Point2D> Circle::generatePointsOnCircle(int num_points) {
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

Circle::Circle(Renderer* renderer, Point2D center, float radius){

    this->center = center;
    this->radius = radius;
    std::vector<Point2D> points;
    points = generatePointsOnCircle(16);//generateRandomPoints(10, center, -100, 100, -100, 100);
    points.push_back(center);
    renderedTriangles = triangulateBowyerWatson(points);
}

// void Circle::debug_insertNextPointInTriang(){

//     auto tmpTr = renderedTriangles;

//     if (debug_stage == 0){
//         debug_IdxNextRenderedPoint++;
//         debug_renderedPoints.push_back(debug_allPoints[debug_IdxNextRenderedPoint]);
//     }

//     tmpTr = debug_triangulateBowyerWatson(debug_renderedPoints, debug_stage);

//     if (debug_stage == 3){
//         renderedTriangles = tmpTr;
//         std::cout << renderedTriangles.size();
//     }

//     debug_stage = (debug_stage + 1) % 4;
    
//     //renderedTriangles = triangulateBowyerWatson(debug_renderedPoints);
// }

std::vector<NodesEdgesTriangles> &Circle::getRenderedTriangles(){
    return renderedTriangles;
}
