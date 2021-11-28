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
    char** shape;
    bool isOutMap;
public:
    ENEMY();
    ENEMY(POSITION pos);
    int getWidth();
    int getHeight();
    virtual string getShapeFile() = 0;
    char** getShape();
    void drawShape();
    POSITION getPos();
    void sound();
    bool isOutOfMap();
    bool move();
    void deleteOldEnemy();
    ~ENEMY();
};

class Car: public ENEMY {
public:
    Car();
    Car(POSITION pos);
    string getShapeFile();
};

class Truck: public ENEMY {
public:
    Truck();
    Truck(POSITION pos);
    string getShapeFile();
};

class Bird: public ENEMY {
public:
    Bird();
    Bird(POSITION pos);
    string getShapeFile();
};

class Dinosaur: public ENEMY {
public:
    Dinosaur();
    Dinosaur(POSITION pos);
    string getShapeFile();
};