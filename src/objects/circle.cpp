#include "circle.h"



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
    color.r = 0.7f;
    color.g = 0.7f;
    color.b = 0.7f;
    edgesColor.r = 1.0f;
    edgesColor.g = 1.0f;
    edgesColor.b = 1.0f;

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

void Circle::setCircleColor(ColorRGB &color){
    this->color = color;
}

void Circle::setEdgesColor(ColorRGB &color){
    this->edgesColor = color;
}

ColorRGB Circle::getCircleColor(){
    return color;
}

ColorRGB Circle::getEdgesColor(){
    return edgesColor;
}
