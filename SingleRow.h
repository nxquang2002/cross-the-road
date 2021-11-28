#include "ConsoleManagement.h"
#include "Enemy.h"
#include "Position.h"
#include <time.h>
#include <vector>

class SINGLEROW {
private:
    vector<ENEMY*> enemies;
    bool dirRight;
    bool redLight;
    int rowY;
public:
    SINGLEROW();
    ~SINGLEROW();
    bool addEnemy(ENEMY* enemy);
    bool addEnemy(int type, POSITION pos);
    int getSize(); //temp
    int getY(); /////temp
    void test(); ////temp
    bool getRedLight();
    void switchLight();  //Green -> red, red -> green;
    void setRedLight();
    bool getDirection();
    void newState();
    void draw();
    void deleteExpireEnemy();
};