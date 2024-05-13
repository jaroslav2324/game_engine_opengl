#pragma once

#include "Point2D.h"
#include "Segment2D.h"

struct mathsCircle{
    mathsCircle(Point2D center, float radius): center(center), radius(radius){};

    int findSegmentIntersections(Segment2D seg, Point2D& int1, Point2D& int2);

    Point2D center;
    float radius;
};
