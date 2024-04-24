#pragma once

struct ColorRGB{
    float r, g, b;

    ColorRGB(float r, float g, float b): r(r), g(g), b(b){};
    ColorRGB() : r(1), g(1), b(1){};

    ColorRGB& operator()(float r, float g, float b);
};