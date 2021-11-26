#include "ConsoleManagement.h"
#include "Enemy.h"
#include "Position.h"
#include <vector>

class SINGLEROW {
private:
    vector<ENEMY*> enemies;
    bool dirRight;
    bool redLight;
public:
    SINGLEROW();
    bool addEnemy(ENEMY* enemy);
    bool getRedLight();
    void setRedLight();
    bool getDirection();
    void newState();
    void draw();
    void deleteExpireEnemy();
};