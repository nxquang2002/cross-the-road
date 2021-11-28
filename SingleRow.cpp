#include "SingleRow.h"

SINGLEROW::SINGLEROW() {
    dirRight = true;
    redLight = false;
}
bool SINGLEROW::addEnemy(ENEMY* enemy) {
    enemies.push_back(enemy);
}

int SINGLEROW::getSize() {
    return enemies.size();
}

int SINGLEROW::getY() {
    gotoXY(0, 5);
    cout << "HAHA: " << enemies[0]->getPos().getY() << "\n";
    return enemies[0]->getPos().getY();
}

void SINGLEROW::test() {
    for (int i = 0; i < enemies.size(); i++) {
        cout << "Enemies[" << i << "]:\n";
        cout << "\tx: " << enemies[i]->getPos().getX() << "\n";
        cout << "\ty: " << enemies[i]->getPos().getY() << "\n";
    }
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
    }
}
void SINGLEROW::deleteExpireEnemy() {
    if (enemies[enemies.size() - 1]->isOutOfMap())
        enemies.pop_back();
    if (enemies[0]->isOutOfMap())
        enemies.erase(enemies.begin());
}


int main()
{
    ENEMY* e1 = new Dinosaur(POSITION(30, 10)); 
    ENEMY* e2 = new Truck(POSITION(55,10)); 
    e1->getShape();
    e2->getShape();
    SINGLEROW r;
    r.addEnemy(e1);
    r.addEnemy(e2);
    r.draw();
    for (int i = 0; i < 6; i++) {
        r.newState();
        r.deleteExpireEnemy();
        //
        if (r.getSize() < 5) {
            POSITION pos;
            if (r.getDirection())
                POSITION pos(SCREEN_LEFT, r.getY()); 
            else
                POSITION pos(SCREEN_RIGHT, r.getY());
            ENEMY* enemy = new Car(pos);
            enemy->getShape();
            r.addEnemy(enemy);
        }
        //
        r.draw();
        //r.test();

        Sleep(600);
    }
    system("pause");
    return 0;
}