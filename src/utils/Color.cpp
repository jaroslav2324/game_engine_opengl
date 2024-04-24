#include "Color.h"

ColorRGB &ColorRGB::operator()(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
    return *this;
}