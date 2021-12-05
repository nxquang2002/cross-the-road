#include "SingleRow.h"

SINGLEROW::SINGLEROW(bool right, int y, int dist, int t) {
    dirRight = right;
    redLight = false;
    rowY = y;
    distance = dist;
    timeRedLight = t;
    gotoXY(123, rowY);
    TextColor(10);          //Draw the light
    cout << (char)254;
    TextColor(15);
}

SINGLEROW::~SINGLEROW() {
    for (int i = 0; i < enemies.size(); ++i) {
        //enemies[i]->~ENEMY();
        delete enemies[i];
    }
}

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
    else if (!enemies.empty() && dirRight && pos.getX() + nEnemy->getWidth() + distance 
        >= enemies.back()->getPos().getX() - enemies.back()->getWidth()) {
        delete nEnemy;
        return false;
    }
    else if(!enemies.empty() && !dirRight && pos.getX() - nEnemy->getWidth() - distance 
        <= enemies.back()->getPos().getX() + enemies.back()->getWidth()){
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
    //gotoXY(0, 5);
    return rowY;
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
    if (redLight) {
        redLight = false;
        gotoXY(123, rowY);
        TextColor(10);
        cout << (char)254;
        gotoXY(123, rowY - 1);
        cout << ' ';
        TextColor(15);
    }
    else {
        gotoXY(123, rowY - 1);
        TextColor(12);
        cout << (char)254;
        gotoXY(123, rowY);
        cout << ' ';
        TextColor(15);
        redLight = true;
    }
}

void SINGLEROW::setRedLight() {
    redLight = true;
}

bool SINGLEROW::getDirection() {
    return dirRight;
}

void SINGLEROW::setDistance(int dist) {
    distance = dist;
}

vector<ENEMY*> SINGLEROW::getListEnemies() const{
    return enemies;
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
        if (!enemies[i]->isOutOfMap())
            enemies[i]->drawShape();
    }
}
void SINGLEROW::deleteExpireEnemy() {
    if (enemies.size() == 0)
        return;
    if (enemies[0]->isOutOfMap()) {
        ENEMY* temp = enemies[0];
        enemies.erase(enemies.begin());
        delete temp;
    }
}