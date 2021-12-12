#include "Rows.h"

ROWS::ROWS(int dist) {
    for (int i = 0; i < ROW_NUM; i++) {
        SINGLEROW* tmp = nullptr;
        if (i % 2)
            tmp = new SINGLEROW(false, 3 + 5 * (i + 1), dist);   //parameters: dirRight, rowY, distance
        else tmp = new SINGLEROW(true, 3 + 5 * (i + 1), dist);
        rows.push_back(tmp);
    }
}


ROWS::~ROWS() {
    for (int i = 0; i < rows.size(); i++) {
        delete rows[i];
    }
}

void ROWS::initializeState(int speed) {
    srand(time(NULL));
    int ran = rand() % 5;
    for (int i = 0; i < ROW_NUM; i++) {
        ran = rand() % 4;
        rows[i]->addEnemy(ran, POSITION(30, 3 + 5 * (i + 1)), speed);     //parameters: type, pos, speed
        ran = rand() % 4;
        rows[i]->addEnemy(ran, POSITION(55, 3 + 5 * (i + 1)), speed);
    }
}


vector<ENEMY*> ROWS::listEnemies(int rowIndex) const {
    return rows[rowIndex]->getListEnemies();
}


//newState ver3
void ROWS::newState(int t, int v, int lightPhase, int epoch) {
    int ran, ran2;
    srand(time(NULL));
    ran = rand() % 5;
    for (int j = 0; j < ROW_NUM; j++) {
        if (rows[j]->getRedLight()) {
            if (rows[j]->getTimeRedLight() <= lightPhase) {
                rows[j]->setTimeRedLight(rows[j]->getTimeRedLight() + 1);
            }
            else {
                rows[j]->switchLight();
            }
        }
        //time stop red light
        if (t % lightPhase == 0) {
            if (!rows[ran]->getRedLight()) {
                rows[ran]->switchLight();
                rows[ran]->setTimeRedLight(0);
            }
        }
    }
    if (t % 3000 == 0) {
        for (int j = 0; j < ROW_NUM; ++j) {
            rows[j]->newState();
            rows[j]->deleteExpireEnemy();
            rows[j]->draw();
        }
    }
    if (t % epoch == 0) {
        //Every epoch, choose random 2 rows to push enemies
        ran = rand() % 5;
        if (rows[ran]->getSize() < 8) { //10
            POSITION pos;
            if (rows[ran]->getDirection()) {
                pos.setX(SCREEN_LEFT);
                pos.setY(rows[ran]->getY());
            }
            else {
                pos.setX(SCREEN_RIGHT);
                pos.setY(rows[ran]->getY());
            }
            srand(time(NULL));
            int type = rand() % 4;
            rows[ran]->addEnemy(type, pos, v);
        }

        ran2 = rand() % 5;
        while (ran2 != ran)
            ran2 = rand() % 5;
        if (rows[ran2]->getSize() < 8) { //10
            POSITION pos;
            if (rows[ran2]->getDirection()) {
                pos.setX(SCREEN_LEFT);
                pos.setY(rows[ran2]->getY());
            }
            else {
                pos.setX(SCREEN_RIGHT);
                pos.setY(rows[ran2]->getY());
            }
            srand(time(NULL));
            int type = rand() % 4;
            rows[ran2]->addEnemy(type, pos, v);
        }
    }
    //gotoXY(5, 38);
    //cout << "t = " << t;
}

void ROWS::saveRows(ofstream& ofs) {
    for (int i = 0; i < ROW_NUM; i++) {
        rows[i]->saveSingleRow(ofs);
    }
}

void ROWS::loadRows(ifstream& ifs, LEVEL level) {
    for (int i = 0; i < ROW_NUM; i++) {
        SINGLEROW* tmp = nullptr;
        if (i % 2)
            tmp = new SINGLEROW(false, 3 + 5 * (i + 1), level.getDistance());   //parameters: dirRight, rowY, distance
        else tmp = new SINGLEROW(true, 3 + 5 * (i + 1), level.getDistance());
        tmp->loadSingleRow(ifs, level);
        rows.push_back(tmp);
    }
}