#pragma once

#include "Point2D.h"

struct Vector2D
{
    Vector2D() : x(0), y(0) {};
    Vector2D(float x, float y) : x(x), y(y) {};
    Vector2D(const Point2D& point);
    float x;
    float y;

    void normalize();
    float length();
    float dot(const Vector2D& vector);

    Vector2D operator+(const Vector2D& vector);
    Vector2D operator-(const Vector2D& vector);
    Vector2D operator*(float scalar);
    Vector2D operator/(float scalar);

    Vector2D& operator=(const Point2D& point);
};
