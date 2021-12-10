#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "ConsoleManagement.h"
#include "Position.h"
#include <fstream>
#include <string>
#define SCREEN_LEFT 10
#define SCREEN_RIGHT 110

class ENEMY {
protected:
    POSITION pos;
    int width;
    int height;
    int speed;
    char** shape;
    bool isOutMap;
    bool dirRight;
public:
    ENEMY();
    ENEMY(POSITION pos, bool dirRight, int spd);
    int getWidth();
    int getHeight();
    virtual string getShapeFile() = 0;
    char** getShape();
    void setSpeed(int spd);
    void drawShape();
    POSITION getPos();
    void sound();
    bool isOutOfMap();
    bool move();
    void deleteOldEnemy();
    void saveEnemy(ofstream& ofs);
    ~ENEMY();
};

class Car : public ENEMY {
public:
    Car();
    Car(POSITION pos, bool dirRight, int spd);
    string getShapeFile();
};

class Truck : public ENEMY {
public:
    Truck();
    Truck(POSITION pos, bool dirRight, int spd);
    string getShapeFile();
};

class Bird : public ENEMY {
public:
    Bird();
    Bird(POSITION pos, bool dirRight, int spd);
    string getShapeFile();
};

class Dinosaur : public ENEMY {
public:
    Dinosaur();
    Dinosaur(POSITION pos, bool dirRight, int spd);
    string getShapeFile();
};

#endif // !_ENEMY_H_