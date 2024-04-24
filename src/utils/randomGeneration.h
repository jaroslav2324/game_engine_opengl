#pragma once

#include <vector>
#include <random>

#include "../maths/Point2D.h"

float randomFloat(float min, float max);
std::vector<Point2D> generateRandomPoints(int numPoints, Point2D center, float minShiftX, float maxShiftX, float minShiftY, float maxShiftY);