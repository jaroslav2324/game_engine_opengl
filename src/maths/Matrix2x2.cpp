#include "Matrix2x2.h"

Matrix2x2::Matrix2x2(){
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            m[i][j] = 0;
        }
    }
}

Matrix2x2::Matrix2x2(float a11, float a12, float a21, float a22){
    m[0][0] = a11;
    m[0][1] = a12;
    m[1][0] = a21;
    m[1][1] = a22;
}

Matrix2x2::Matrix2x2(Vector2D &vec1, Vector2D &vec2){
    m[0][0] = vec1.x;
    m[0][1] = vec2.x;
    m[1][0] = vec1.y;
    m[1][1] = vec2.y;
}

// Matrix2x2 Matrix2x2::operator*(const Matrix2x2 &other){
//     Matrix2x2 result;
    
// }

Vector2D Matrix2x2::operator*(const Vector2D &vec){
    Vector2D result;
    result.x = m[0][0] * vec.x + m[0][1] * vec.y;
    result.y = m[1][0] * vec.x + m[1][1] * vec.y;
    return result;
}

float Matrix2x2::det(){
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

Matrix2x2 Matrix2x2::T(){
    return Matrix2x2(m[0][0], m[1][0], m[0][1], m[1][1]);
}
