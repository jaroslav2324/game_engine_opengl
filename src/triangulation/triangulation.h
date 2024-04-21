#include <vector>
#include <algorithm>
#include <iostream>

#include "structures.h"

NodesEdgesTriangles createSuperTriangle(std::vector<Node> points);

std::vector<NodesEdgesTriangles> triangulateBowyerWatson(std::vector<Node> points);

void insertPointInTriangulation(Node point, std::vector<NodesEdgesTriangles>& triangulation);
