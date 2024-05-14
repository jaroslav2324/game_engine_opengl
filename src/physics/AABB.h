#pragma once

// Structure representing an Axis-Aligned Bounding Box (AABB)
struct AABB{
    AABB(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {};
    bool intersects(AABB& second);
    float x, y;  // The x and y coordinates of the top-left corner of the AABB
    float w, h;  // The width and height of the AABB
};
