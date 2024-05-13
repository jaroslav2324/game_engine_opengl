#include "mathsCircle.h"
#include "mathsRect.h"

int mathsCircle::findSegmentIntersections(Segment2D seg, Point2D &intersection1, Point2D &intersection2){
    float dx, dy, A, B, C, det, t;

    dx = seg.p2.x - seg.p1.x;
    dy = seg.p2.y - seg.p1.y;

    A = dx * dx + dy * dy;
    B = 2 * (dx * (seg.p1.x - center.x) + dy * (seg.p1.y - center.y));
    C = (seg.p1.x - center.x) * (seg.p1.x - center.x) + (seg.p1.y - center.y) * (seg.p1.y - center.y) - radius * radius;

    det = B * B - 4 * A * C;
    if ((A <= 0.000001) || (det < -1e-6)){
        return 0;
    }
    else if (std::abs(det) - 1e-6 < 1e-6){
        // One solution.
        t = -B / (2 * A);
        Point2D int1(seg.p1.x + t * dx, seg.p1.y + t * dy);
        if (seg.isPointOnSegment(int1)){
            intersection1 = int1;
            return 1;
        }
        return 0;
    }
    else {
        // Two solutions.
        t = (float)((-B + sqrt(det)) / (2 * A));
        Point2D int1(seg.p1.x + t * dx, seg.p1.y + t * dy);
        t = (float)((-B - sqrt(det)) / (2 * A));
        Point2D int2(seg.p1.x + t * dx, seg.p1.y + t * dy);
        bool int1OnSeg = seg.isPointOnSegment(int1);
        bool int2OnSeg = seg.isPointOnSegment(int2);

        if (int1OnSeg && !int2OnSeg){
            intersection1 = int1;
            return 1;
        }
        if (!int1OnSeg && int2OnSeg){
            intersection1 = int2;
            return 1;
        }
        if (int1OnSeg && int2OnSeg){
            intersection1 = int1;
            intersection2 = int2;
            return 2;
        }

        return 0;
    }
}

bool mathsCircle::intersectsCircle(mathsCircle &second){
    float distance = sqrt(pow(center.x - second.center.x , 2) 
    + pow(center.y - second.center.y , 2));
    if (distance < radius + second.radius)
        return true;
    return false;
}

bool mathsCircle::intersectsRect(mathsRect &rect){
    Point2D posCir = center;
    Point2D posRect = Point2D(rect.x + rect.width / 2, rect.y + rect.height / 2);
    float rectWidth = rect.width;
    float rectHeight = rect.height;

    float distanceX = std::abs(posCir.x - posRect.x);
    float distanceY = std::abs(posCir.y - posRect.y);

    if (distanceX > (rectWidth / 2 + radius))
        return false;
    if (distanceY > (rectHeight / 2 + radius))
        return false;
    if (distanceX <= (rectWidth / 2))
        return true;
    if (distanceY <= (rectHeight / 2))
        return true;

    float squaredCornerDistance = pow((distanceX - rectWidth / 2), 2) + pow((distanceY - rectHeight / 2), 2);
    return (squaredCornerDistance <= pow(radius, 2));
}
