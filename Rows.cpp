#include "Rows.h"

ROWS::ROWS() {

    for (int i = 0; i < ROW_NUM; i++) {
        SINGLEROW* tmp = nullptr;
        if(i % 2)
            tmp = new SINGLEROW(false, 3 + 5 * i, 5);
        else tmp = new SINGLEROW(true, 3 + 5 * i, 5);
        rows.push_back(tmp);
    }
}

ROWS::~ROWS() {
    for (int i = 0; i < rows.size(); i++) {
        rows[i]->~SINGLEROW();
        delete rows[i];
    }
        
}

void ROWS::newState(int t, int v) {
    int ran;
    srand(time(NULL));
    for (int i = 0; i < ROW_NUM; i++) {
        ran = rand() % 4;
        rows[i]->addEnemy(ran, POSITION(30, 3 + 5 * i), v);
        ran = rand() % 4;
        rows[i]->addEnemy(ran, POSITION(55, 3 + 5 * i), v);
    }

    POSITION pos;
    for (int i = 0; i < 100; ++i) {

        ran = rand() % 5;
        for (int j = 0; j < ROW_NUM; j++) {
            if (j % 2 != 0) {
                cout << '.' << endl;
            }
            if (rows[j]->getRedLight()) {
                if (rows[j]->getTimeRedLight() <= t) {
                    rows[j]->setTimeRedLight(rows[j]->getTimeRedLight() + 1);
                }
                else {
                    rows[j]->switchLight();
                }
            }
            //time stop red light
            if (i % t == 0) {
                if (!rows[ran]->getRedLight()) {
                    rows[ran]->switchLight();
                    rows[ran]->setTimeRedLight(0);
                }
            }
            rows[j]->newState();
            rows[j]->deleteExpireEnemy();
            rows[j]->draw();
        }
        /*
        if (rows[i % 5]->getSize() < 5) {
            //POSITION pos;
            if (rows[i % 5]->getDirection()) {
                pos.setX(SCREEN_LEFT);
                pos.setY(rows[i % 5]->getY());
            }
            else {
                pos.setX(SCREEN_RIGHT);
                pos.setY(rows[i % 5]->getY());
            }
            //ran = rand() % 4;
            int type = rand() % 4;
            bool dir = rows[i % 5]->getDirection();
            rows[i % 5]->addEnemy(type, pos, dir);
        }*/
        if (i % 3 == 0) {       //Every 3 times, add 1 enemy, choose 1 random row to push.
            ran = rand() % 5;
            if (rows[ran]->getSize() < 5) {
                if (rows[ran]->getDirection()) {
                    pos.setX(SCREEN_LEFT);
                    pos.setY(rows[ran]->getY());
                }
                else {
                    pos.setX(SCREEN_RIGHT);
                    pos.setY(rows[ran]->getY());
                }
                //ran = rand() % 4;
                int type = rand() % 4;
                rows[ran]->addEnemy(type, pos, v);
            }
        }
        Sleep(150);
    }
    return;
}


int main()
{
    ROWS R;
    R.newState(20, 2);
    return 0;
}