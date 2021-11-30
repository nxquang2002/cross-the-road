#include "SingleRow.h"

SINGLEROW::SINGLEROW(bool right, int y, int dist, int t) {
    dirRight = right;
    redLight = false;
    rowY = y;
    distance = dist;
}

SINGLEROW::~SINGLEROW() {
    for (int i = 0; i < enemies.size(); ++i)
        delete enemies[i];
}
bool SINGLEROW::addEnemy(ENEMY* enemy) {
    enemies.push_back(enemy);
    return true;
}

//them ham add voi parameter tuy loai.
bool SINGLEROW::addEnemy(int type, POSITION pos, int speed) {
    ENEMY* nEnemy = nullptr;
    switch (type) {
    case (0):
        nEnemy = new Car(pos, dirRight, speed);
        break;
    case(1):
        nEnemy = new Truck(pos, dirRight, speed);
        break;
    case 2:
        nEnemy = new Bird(pos, dirRight, speed);
        break;
    case 3:
        nEnemy = new Dinosaur(pos, dirRight, speed);
        break;
    }
    nEnemy->getShape();
    if (nEnemy->isOutOfMap()) {
        delete nEnemy;
        return false;
    }
    else if (!enemies.empty() && dirRight && pos.getX() + nEnemy->getWidth() + distance >= enemies.back()->getPos().getX() - enemies.back()->getWidth()) {
        delete nEnemy;
        return false;
    }
    else if(!enemies.empty() && !dirRight && pos.getX() - nEnemy->getWidth() - distance <= enemies.back()->getPos().getX() + enemies.back()->getWidth()){
        delete nEnemy;
        return false;
    }
    else {
        enemies.push_back(nEnemy);
        return true;
    }
    return true;
}

int SINGLEROW::getSize() {
    return enemies.size();
}

int SINGLEROW::getY() {
    gotoXY(0, 5);
    return enemies[0]->getPos().getY();
}

void SINGLEROW::test() {
    for (int i = 0; i < enemies.size(); i++) {
        cout << "Enemies[" << i << "]:\n";
        cout << "\tx: " << enemies[i]->getPos().getX() << "\n";
        cout << "\ty: " << enemies[i]->getPos().getY() << "\n";
    }
}

int SINGLEROW::getTimeRedLight() {
    return timeRedLight;
}
void SINGLEROW::setTimeRedLight(int t) {
    timeRedLight = t;
}

bool SINGLEROW::getRedLight() {
    return redLight;
}

void SINGLEROW::switchLight() {
    if (redLight)
        redLight = false;
    else redLight = true;
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
//Không để light cứng như vậy
//Nếu redlight thì vẽ đèn đỏ ra, xóa đèn xanh và ngược lại
//Về direction thì xử lí như thế nào?

void SINGLEROW::draw()
{
    for (int i = 0; i < enemies.size(); i++) {
        if (!enemies[i]->isOutOfMap())
            enemies[i]->drawShape();
    }
}
void SINGLEROW::deleteExpireEnemy() {
    if (enemies[enemies.size() - 1]->isOutOfMap()) {
        ENEMY* temp = enemies.back();
        enemies.pop_back();
        delete temp;
    }
    if (enemies[0]->isOutOfMap()) {
        ENEMY* temp = enemies[0];
        enemies.erase(enemies.begin());
        delete temp;
    }
}