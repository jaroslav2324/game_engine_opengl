#include "Segment2D.h"

float Segment2D::length(){
    return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

bool Segment2D::isPointOnSegment(Point2D point)
{
    float AB = sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
    float AP = sqrt((point.x-p1.x)*(point.x-p1.x)+(point.y-p1.y)*(point.y-p1.y));
    float PB = sqrt((p2.x-point.x)*(p2.x-point.x)+(p2.y-point.y)*(p2.y-point.y));
    if(std::abs(AB - (AP + PB)) < 1e-6)
        return true;
    return false;
}

int Segment2D::findSegmentIntersection(Segment2D &second, Point2D &intersection){
    // check segments` lengths are not 0
    if (this->length() < 1e-6 || second.length() < 1e-6){
        return 0;
    }

    float denominator = ((second.p2.y - second.p1.y) * (p2.x - p1.x) - (second.p2.x - second.p1.x) * (p2.y - p1.y));
    
    // segments are parallel
    if (std::abs(denominator) < 1e-6){
        return false;
    }

    float ua = ((second.p2.x - second.p1.x) * (p1.y - second.p1.y) - (second.p2.y - second.p1.y) * (p1.x - second.p1.x)) / denominator;
    float ub = ((p2.x - p1.x) * (p1.y - second.p1.y) - (p2.y - p1.y) * (p1.x - second.p1.x)) / denominator;

    if (ua < 0 || ua > 1 || ub < 0 || ub > 1){
        return 0;
    }

    intersection.x = p1.x + ua * (p2.x - p1.x);
    intersection.y = p1.y + ua * (p2.y - p1.y);
    return 1;
}


