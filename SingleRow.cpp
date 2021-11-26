#include "SingleRow.h"

SINGLEROW::SINGLEROW() {
    dirRight = true;
    redLight = true;
}
bool SINGLEROW::addEnemy(ENEMY* enemy) {
    enemies.push_back(enemy);
}
bool SINGLEROW::getRedLight() {
    return redLight;
}    
void SINGLEROW::setRedLight() {
    redLight = true;
}
    
bool SINGLEROW::getDirection() {
    return dirRight;
}
    
void SINGLEROW::newState() {
    if (redLight)
        return;
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->move();
    }
}
    
void SINGLEROW::deleteExpireEnemy() {
    if (enemies[enemies.size() - 1]->isOutOfMap())
        enemies.pop_back();
    if (enemies[0]->isOutOfMap())
        enemies.erase(enemies.begin());
}