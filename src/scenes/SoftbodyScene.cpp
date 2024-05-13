#include "Scenes.h"

void loadSoftbodyScene(ObjectManager &objManager){
    loadBorders(objManager);
    Softbody* rect = objManager.createSoftRect({300, 500}, 200, 300);
    rect->setGravityScale(0.1f);

    Softbody* circle = objManager.createSoftCircle({700, 300}, 50, 8);
    circle->setGravityScale(0.1f);
    circle->addVelocity({-200, 50});
}