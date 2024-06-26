#include "SoftbodyRect.h"

SoftbodyRect::SoftbodyRect(Point2D center, float width, float height)
: Softbody(SoftbodyType::SOFTBODY_RECT){

    float tempStifness = 0.1f;

    points.push_back(SoftbodyPoint({center.x - width / 2, center.y - height / 2}));
    points.push_back(SoftbodyPoint({center.x + width / 2, center.y - height / 2}));
    points.push_back(SoftbodyPoint({center.x + width / 2, center.y + height / 2}));
    points.push_back(SoftbodyPoint({center.x - width / 2, center.y + height / 2}));

    springs.push_back(SoftbodySpring(&points[0], &points[1], width, tempStifness, 0.1f));
    springs.push_back(SoftbodySpring(&points[1], &points[2], height, tempStifness, 0.1f));
    springs.push_back(SoftbodySpring(&points[2], &points[3], width, tempStifness, 0.1f));
    springs.push_back(SoftbodySpring(&points[3], &points[0], height, tempStifness, 0.1f));

    float diagLen = sqrt(width * width + height * height);
    springs.push_back(SoftbodySpring(&points[0], &points[2], diagLen, tempStifness, 0.1f));
    springs.push_back(SoftbodySpring(&points[1], &points[3], diagLen, tempStifness, 0.1f));
}

float SoftbodyRect::getWidth(){
    return width;
}

float SoftbodyRect::getHeight(){
    return height;
}
