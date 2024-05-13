#include "mathsRect.h"

mathsRect::mathsRect(){
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
}

mathsRect::mathsRect(float x, float y, float width, float height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

mathsRect::mathsRect(Point2D upperLeft, float width, float height){
    this->x = upperLeft.x;
    this->y = upperLeft.y;
    this->width = width;
    this->height = height;
}

void mathsRect::getSegments(Segment2D *segs){
    segs[0] = Segment2D(Point2D(x, y), Point2D(x + width, y));
    segs[1] = Segment2D(Point2D(x + width, y), Point2D(x + width, y + height));
    segs[2] = Segment2D(Point2D(x + width, y + height), Point2D(x, y + height));
    segs[3] = Segment2D(Point2D(x, y + height), Point2D(x, y));
}

Vector2D mathsRect::getIntersectionLineVecCircle(mathsCircle &circle){
    float radius = circle.radius;
    Point2D cirCenter = circle.center;

    // create segments
    Segment2D segments[4];
    getSegments(segments);

    int countInters = 0;
    Point2D inters[8];
    int idxCurrEmptyInter = 0;
    Point2D inter1;
    Point2D inter2;
    for (int segIdx = 0; segIdx < 4; segIdx++){
        int count = mathsCircle(cirCenter, radius)
        .findSegmentIntersections(segments[segIdx], inter1, inter2);
        if (count == 2){
            inters[idxCurrEmptyInter] = inter1;
            idxCurrEmptyInter++;
            inters[idxCurrEmptyInter] = inter2;
            idxCurrEmptyInter++;
        }
        if (count == 1){
            inters[idxCurrEmptyInter] = inter1;
            idxCurrEmptyInter++;
        }
        countInters += count;
    }
    if (countInters < 1 || countInters > 2){
        std::cout << "ERROR: amount intersections of rect and circle is " << countInters << "\n";
    }
    // corner collision
    if (countInters == 1){
        Vector2D fromCenterVec = inters[0] - cirCenter;
        std::cout << "Corner collision" << std::endl;
        // TODO change
        return Vector2D(-fromCenterVec.y, fromCenterVec.x);
    }
    inter1 = inters[0];
    inter2 = inters[1];
    return Vector2D(inter1.x - inter2.x, inter1.y - inter2.y);
}

Vector2D mathsRect::getIntersectionLineVecRect(mathsRect &rect){
    // create segments
    Segment2D segments1[4];
    getSegments(segments1);
    Segment2D segments2[4];
    rect.getSegments(segments2);

    int countInterPoints = 0;
    Point2D interPoints[16];
    int currInterPidx = 0;
    Point2D interP;
    for (int idx1 = 0; idx1 < 4; idx1++){
        for (int idx2 = idx1 + 1; idx2 < 4; idx2++){
            int count = segments1[idx1].findSegmentIntersection(segments2[idx2], interP);
            if (count == 1){
                interPoints[currInterPidx] = interP;
                currInterPidx++;
                countInterPoints += count;
            }
        }
    }
    if (countInterPoints < 1 || countInterPoints > 2){
        std::cout << "TODO ERROR: Rect Rect intersection points wrong count: " << countInterPoints << "\n";
    }

    return Vector2D(interPoints[0].x - interPoints[1].x, interPoints[0].y - interPoints[1].y);
}
