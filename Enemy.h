#include "ConsoleManagement.h"
//#include "SingleRow.h"
#include "Position.h"
#include <fstream>
#include <string>
#define SCREEN_LEFT 10
#define SCREEN_RIGHT 110

class ENEMY {
protected:
    Position pos;
    int width;
    int height;
    char** shape;
    bool isOutMap;
public:
    ENEMY();
    ENEMY(Position pos);
    int getWidth();
    int getHeight();
    virtual string getShapeFile() = 0;
    char** getShape();
    void drawShape();
    Position getPos();
    void sound();
    bool isOutOfMap();
    bool move();
    void deleteOldEnemy();
    ~ENEMY();
    
};

class Car: public ENEMY {
public:
    Car();
    Car(Position pos);
    string getShapeFile();
};

class Truck: public ENEMY {
public:
    Truck();
    Truck(Position pos);
    string getShapeFile();
};

class Bird: public ENEMY {
public:
    Bird();
    Bird(Position pos);
    string getShapeFile();
};

class Dinosaur: public ENEMY {
public:
    Dinosaur();
    Dinosaur(Position pos);
    string getShapeFile();
};