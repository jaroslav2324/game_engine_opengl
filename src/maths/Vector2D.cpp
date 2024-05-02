#include "Vector2D.h"

Vector2D::Vector2D(const Point2D &point){
    x = point.x;
    y = point.y;
}

Vector2D& Vector2D::normalize(){
    float len = length();

    if(len != 0){
        x /= len;
        y /= len;
    }
    return *this;
}

float Vector2D::length(){
    return sqrt(x * x + y * y);
}

float Vector2D::dot(const Vector2D &vector){
    return x * vector.x + y * vector.y;
}

bool Vector2D::isZeroVector(){
    float epsilon = 1e-3;
    if(std::abs(x) < epsilon && std::abs(y) < epsilon){
        return true;
    }
    return false;
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

Vector2D &Vector2D::operator+=(const Vector2D &vector){
    x += vector.x;
    y += vector.y;
    return *this;
}

Vector2D &Vector2D::operator-=(const Vector2D &vector){
    x -= vector.x;
    y -= vector.y;
    return *this;
}

Vector2D &Vector2D::operator*=(float scalar){
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2D &Vector2D::operator/=(float scalar){
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector2D &Vector2D::operator=(const Point2D &point)
{
    x = point.x;
    y = point.y;
    return *this;
}

Vector2D operator*(float scalar, Vector2D &vector){
    return vector.operator*(scalar);
}
