#pragma once

#include "../utils/pointsGeneration.h"
#include "../objects/ObjectManager.h"

// creates basic scene
void loadBasicScene(ObjectManager& objManager);
// creates rest scene with rects
void loadTestRectsScene(ObjectManager& objManager);
// creates poing pong scene
void loadPingPong(ObjectManager& objManager);
// creates softbody scene
void loadSoftbodyScene(ObjectManager& objManager);

void loadBorders(ObjectManager& objManager);

