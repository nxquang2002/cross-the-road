#include "SingleRow.h"

SINGLEROW::SINGLEROW() {
    dirRight = true;
    redLight = false;
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
bool SINGLEROW::addEnemy(int type, POSITION pos) {
    ENEMY* nEnemy = nullptr;
    switch (type) {
    case (0):
        nEnemy = new Car(pos);
        break;
    case(1):
        nEnemy = new Truck(pos);
        break;
    case 2:
        nEnemy = new Bird(pos);
        break;
    case 3:
        nEnemy = new Dinosaur(pos);
        break;
    }
    nEnemy->getShape();
    if (nEnemy->isOutOfMap()) {
        delete nEnemy;
        return false;
    }
    else if (!enemies.empty() && pos.getX() + nEnemy->getWidth() + 5 >= enemies.back()->getPos().getX() - enemies.back()->getWidth()) {
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

//void newState(bool red);


void SINGLEROW::draw()
{
    for (int i = 0; i < enemies.size(); i++) {
        if(!enemies[i]->isOutOfMap())
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


int main()
{
    /*
    ENEMY* e1 = new Dinosaur(POSITION(30, 10));
    ENEMY* e2 = new Truck(POSITION(55, 10));
    e1->getShape();
    e2->getShape();
    SINGLEROW r;
    r.addEnemy(e1);
    r.addEnemy(e2);
    r.draw();
    for (int i = 0; i < 100; i++) {
        r.newState();
        r.deleteExpireEnemy();
        //
        if (r.getSize() < 5) {
            POSITION pos;
            if (r.getDirection()) {
                POSTION pos(SCREEN_LEFT, r.getY());
            }
            else {
                pos.setX(SCREEN_RIGHT);
                pos.setY(r.getY());
            }
            ENEMY* enemy = new Car(pos);
            enemy->getShape();
            r.addEnemy(enemy);
        }
        //
        r.draw();
        //r.test();

        Sleep(200);
    }
    delete e1;
    delete e2;*/

    SINGLEROW r;
    int ran;
    srand(time(NULL));
    ran = rand() % 4;
    r.addEnemy(ran, POSITION(30, 10));
    ran = rand() % 4;
    r.addEnemy(ran, POSITION(55, 10));
    for (int i = 0; i < 150; ++i) {
        r.newState();
        r.deleteExpireEnemy();
        if (r.getSize() < 5) {
            POSITION pos;
            if (r.getDirection()) {
                pos.setX(SCREEN_LEFT);
                pos.setY(r.getY());
            }
            else {
                pos.setX(SCREEN_RIGHT);
                pos.setY(r.getY());
            }
            ran = rand() % 4;
            r.addEnemy(ran, pos);
        }
        r.draw();
        Sleep(150);
    }
    r.~SINGLEROW();
    system("pause");
    return 0;
}