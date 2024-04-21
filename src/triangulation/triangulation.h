#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "structures.h"
#include "../maths/Point2D.h"

NodesEdgesTriangles createSuperTriangle(std::vector<Node> points);

std::vector<NodesEdgesTriangles> triangulateBowyerWatson(std::vector<Point2D> points);

void insertPointInTriangulation(Node point, std::vector<NodesEdgesTriangles>& triangulation);
