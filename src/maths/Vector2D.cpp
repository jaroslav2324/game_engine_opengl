#include "Vector2D.h"

Vector2D::Vector2D(const Point2D &point){
    x = point.x;
    y = point.y;
}

Vector2D Vector2D::normalize(){
    Vector2D res(x, y);
    float len = length();

    if(len != 0){
        res.x /= len;
        res.y /= len;
    }
    return res;
}

float Vector2D::length(){
    return sqrt(x * x + y * y);
}

float Vector2D::dot(const Vector2D &vector){
    return x * vector.x + y * vector.y;
}

float Vector2D::angle(Vector2D &second){
    return acos(this->dot(second) / (this->length() * second.length()));
}

Vector2D Vector2D::project(Vector2D &onThis){
    return this->dot(onThis) * onThis / (onThis.length() * onThis.length());
}

Vector2D Vector2D::rotate(float angle){
    float s = sin(angle);
    float c = cos(angle);
    return Vector2D(x * c - y * s, x * s + y * c);
}

bool Vector2D::isZeroVector(){
    float epsilon = 1e-3;
    if(std::abs(x) < epsilon && std::abs(y) < epsilon){
        return true;
    }
    return false;
}

void Vector2D::debugPrint(){
    std::cout << "Vector2D: " << x << ", " << y << std::endl;
}

Vector2D Vector2D::operator-(){
    Vector2D res(-x, -y);
    return res;
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

Vector2D Vector2D::operator/(float scalar){
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

Vector2D &Vector2D::operator=(const Point2D &point){
    x = point.x;
    y = point.y;
    return *this;
}

Vector2D operator*(float scalar, Vector2D &vector){
    return vector.operator*(scalar);
}
