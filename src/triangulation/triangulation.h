#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include <cmath>

#include <GL/glut.h>

#include "structures.h"
#include "../maths/Point2D.h"

NodesEdgesTriangles createSuperTriangle(std::vector<Node> points);

std::vector<NodesEdgesTriangles> triangulateBowyerWatson(std::vector<Point2D> points);

void insertPointInTriangulation(Node point, std::vector<NodesEdgesTriangles>& triangulation);

// void debug_drawTriangs(std::vector<NodesEdgesTriangles> &trianglesVec);
// void debug_drawPoint(Node &point);
// void debug_insertPointInTriangulation(Node point, std::vector<NodesEdgesTriangles> &triangulation, int stage);
// std::vector<NodesEdgesTriangles> debug_triangulateBowyerWatson(std::vector<Point2D> points, int stage);
// void debug_drawEdges(std::vector<NodesEdgesTriangles> &trianglesVec);
// void debug_calculate_circle(const NodesEdgesTriangles& triangle, Node& center, float& radius);
// void debug_draw_circle(const Node& center, float radius, int num_segments);
// Node debug_coordsToNormed(Node& node);
