#include "Vector2D.h"

Vector2D::Vector2D(const Point2D &point){
    x = point.x;
    y = point.y;
}

Vector2D Vector2D::operator+(const Vector2D &vector){
    return Vector2D(x + vector.x, y + vector.y);
}

Vector2D Vector2D::operator-(const Vector2D &vector){
    return Vector2D(x - vector.x, y - vector.y);
}

Vector2D Vector2D::operator*(float scalar){
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(float scalar)
{
    return Vector2D(x / scalar, y / scalar);
}

Vector2D &Vector2D::operator=(const Point2D &point)
{
    x = point.x;
    y = point.y;
    return *this;
}