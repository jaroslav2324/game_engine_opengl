#pragma once

struct SoftbodyPointCollisionShape{
    SoftbodyPointCollisionShape() : radius(10.0f) {};
    SoftbodyPointCollisionShape(float radius) : radius(radius) {};

    float radius;
};
