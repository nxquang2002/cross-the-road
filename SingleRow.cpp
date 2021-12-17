#include "SingleRow.h"

SINGLEROW::SINGLEROW(bool right, int y, int dist, int t) {
    dirRight = right;
    redLight = false;
    rowY = y;
    distance = dist;
    timeRedLight = t;
}

SINGLEROW::~SINGLEROW() {
    for (int i = 0; i < enemies.size(); ++i) {
        delete enemies[i];
        enemies[i] = nullptr;
    }
    enemies.clear();
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
    else if (!enemies.empty() && !dirRight && pos.getX() - nEnemy->getWidth() - distance
        <= enemies.back()->getPos().getX() + enemies.back()->getWidth()) {
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

vector<ENEMY*> SINGLEROW::getListEnemies() const {
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

void SINGLEROW::saveSingleRow(ofstream& ofs) {
    int n = enemies.size();
    ofs.write((char*)&dirRight, sizeof(bool));
    ofs.write((char*)&redLight, sizeof(bool));
    ofs.write((char*)&timeRedLight, sizeof(int));
    ofs.write((char*)&n, sizeof(int));
    for (int i = 0; i < n; i++) {
        enemies[i]->saveEnemy(ofs);
    }
}

void SINGLEROW::loadSingleRow(ifstream& ifs, LEVEL level) {
    int n, w;
    POSITION p;
    ifs.read((char*)&dirRight, sizeof(bool));
    ifs.read((char*)&redLight, sizeof(bool));
    ifs.read((char*)&timeRedLight, sizeof(int));
    ifs.read((char*)&n, sizeof(int));
    for (int i = 0; i < n; i++) {
        ENEMY* tmp = nullptr;
        ifs.read((char*)&p, sizeof(POSITION));
        ifs.read((char*)&w, sizeof(int));
        switch (w) {
        //2, 6, 7, 8 are the width of enemy type, they're unique.
        case 2:     
            addEnemy(2, p, level.getSpeed());      //Bird;
            break;
        case 6:
            addEnemy(0, p, level.getSpeed());      //Car
            break;
        case 7:
            addEnemy(3, p, level.getSpeed());      //Dinosaur
            break;
        case 8:
            addEnemy(1, p, level.getSpeed());      //Truck
            break;
        }
    }
} 