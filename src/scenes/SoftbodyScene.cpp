#include "Scenes.h"

void loadSoftbodyScene(ObjectManager &objManager){
    loadBorders(objManager);
    Softbody* rect = objManager.createSoftRect({300, 500}, 200, 300);
    // rect->setGravityScale(0);
}