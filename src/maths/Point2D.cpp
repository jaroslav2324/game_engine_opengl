#include "Point2D.h"

Point2D &Point2D::operator=(const Point2D &second)
{
    x = second.x;
    y = second.y;
    return *this;
}

Point2D Point2D::operator-(const Point2D &second)
{
    return Point2D(x - second.x, y - second.y);
}

Point2D Point2D::operator+(const Point2D &second){
    return Point2D(x + second.x, y + second.y);
}

Point2D Point2D::operator*(float scalar){
    return Point2D(x * scalar, y * scalar);
}

Point2D Point2D::operator/(float scalar){
    return Point2D(x / scalar, y / scalar);
}

float Point2D::distanceTo(Point2D &second){
    float xDiff = x - second.x;
    float yDiff = y - second.y;
    return sqrt(xDiff * xDiff + yDiff * yDiff);
}
