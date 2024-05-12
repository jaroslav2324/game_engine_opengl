#pragma once

#include "SoftbodyPoint.h"

struct SoftbodySpring{
    SoftbodySpring(SoftbodyPoint* p1, SoftbodyPoint* p2, float restLength, float strifness, float damping):
    point1(p1), point2(p2), restLength(restLength), stiffness(stiffness), damping(damping){};
    
    SoftbodyPoint* point1;
    SoftbodyPoint* point2;
    float restLength;
    float stiffness;
    float damping;

    void updatePhysics();
};
