#include "SingleRow.h"

SINGLEROW::SINGLEROW() {
    dirRight = true;
    redLight = false;
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
        enemies[i]->deleteOldEnemy();
        enemies[i]->move();
    }
}
void SINGLEROW::draw()
{
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->drawShape();
        Sleep(200);
    }
}
void SINGLEROW::deleteExpireEnemy() {
    if (enemies[enemies.size() - 1]->isOutOfMap())
        enemies.pop_back();
    if (enemies[0]->isOutOfMap())
        enemies.erase(enemies.begin());
}


/*int main()
{
    ENEMY* e1 = new Dinosaur(Position(25, 10));
    ENEMY* e2 = new Truck(Position(45,10));
    e1->getShape();
    e2->getShape();
    SINGLEROW r;
    r.addEnemy(e1);
    r.addEnemy(e2);
    r.draw();
    for (int i = 0; i < 3; i++) {
        r.newState();
        r.draw();
        Sleep(200);
    }
    system("pause");
    return 0;
}*/