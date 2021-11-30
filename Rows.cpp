#include "Rows.h"

ROWS::ROWS() {

    for (int i = 0; i < ROW_NUM; i++) {
        SINGLEROW* tmp = new SINGLEROW(3 + 5 * i, 3);
        rows.push_back(tmp);
    }
}

ROWS::~ROWS() {
    for (int i = 0; i < rows.size(); i++)
        delete rows[i]; 
}

void ROWS::newState(int t, int v) {
    int ran;
    srand(time(NULL));
    for (int i = 0; i < ROW_NUM; i++) {
        ran = rand() % 4;
        rows[i]->addEnemy(ran, POSITION(30, 3 + 5 * i));
        ran = rand() % 4;
        rows[i]->addEnemy(ran, POSITION(55, 3 + 5 * i));
    }

    rows[0]->draw();
    POSITION pos;
    for (int i = 0; i < 100; ++i) {
        
        ran = rand() % 5;
        for (int j = 0; j < ROW_NUM; j++) {
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
            /*if (rows[j]->getSize() < 5) {
                //POSITION pos;
                if (rows[j]->getDirection()) {
                    pos.setX(SCREEN_LEFT);
                    pos.setY(rows[j]->getY());
                }
                else {
                    pos.setX(SCREEN_RIGHT);
                    pos.setY(rows[j]->getY());
                }
                ran = rand() % 4;
                //rows[j]->addEnemy(ran, pos);
            }*/
            rows[j]->draw();
        }
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
            ran = rand() % 4;
            rows[i % 5]->addEnemy(ran, pos);
        }
        Sleep(40);
    }
    system("pause");
    return;
}


int main()
{
    ROWS R;
    R.newState(10, 1);
    return 0;
}