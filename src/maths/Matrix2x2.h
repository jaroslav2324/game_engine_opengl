#pragma once

#include "Vector2D.h"

struct Matrix2x2
{
    Matrix2x2();
    Matrix2x2(float a11, float a12, float a21, float a22);
    Matrix2x2(Vector2D& vec1, Vector2D& vec2);

    // Matrix2x2 operator*(const Matrix2x2& other);
    Vector2D operator*(const Vector2D& vec);

    float det();
    // transpose
    Matrix2x2 T();

    float m[2][2];
};


