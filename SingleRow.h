#ifndef _SINGLEROW_H_
#define _SINGLEROW_H_

#include "ConsoleManagement.h"
#include "Enemy.h"
#include "Position.h"
#include <time.h>
#include <vector>
#include <assert.h>

class SINGLEROW {
private:
    vector<ENEMY*> enemies;
    bool dirRight;
    bool redLight;
    int rowY;
    int distance;
    int timeRedLight;
public:
    SINGLEROW(bool right, int y = 0, int dist = 0, int t = 0);
    ~SINGLEROW();
    bool addEnemy(ENEMY* enemy);
    bool addEnemy(int type, POSITION pos, int speed);
    int getSize(); //temp
    int getY(); /////temp
    void test(); ////temp
    int getTimeRedLight();
    void setTimeRedLight(int t);
    bool getRedLight();
    void switchLight();  //Green -> red, red -> green;
    void setRedLight();
    bool getDirection();
    void newState();
    void draw();
    void deleteExpireEnemy();
};

#endif // !_SINGLEROW_H_