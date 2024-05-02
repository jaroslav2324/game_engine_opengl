#include "PhysicsParameters.h"

int PhysicsParameters::setElastic(float coeffElasticity){

    if (!(coeffElasticity >= 0 && coeffElasticity <= 1)){
        // TODO add error handling
        std::cout << "Attemt to set elasticity coefficient out of bounds!\n";
        return -1;
    }

    this->elasticBody = true;
    this->coeffElasticity = coeffElasticity;

    return 0;
}

void PhysicsParameters::unsetElastic(){
    this->elasticBody = false;
}

bool PhysicsParameters::isElastic(){
    return this->elasticBody;
}

float PhysicsParameters::getCoeffElasticity(){
    return this->coeffElasticity;
}
