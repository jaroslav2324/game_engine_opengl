#pragma once
#include "Point2D.h"
#include "Vector2D.h" 

struct Segment2D{
    Segment2D(): p1(0, 0), p2(0, 0){};
    Segment2D(Point2D p1, Point2D p2): p1(p1), p2(p2){};

    float length();

    bool isPointOnSegment(Point2D point);

    int findSegmentIntersection(Segment2D& second, Point2D& intersection);

    Point2D p1;
    Point2D p2;
};