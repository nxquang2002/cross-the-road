#include "ConsoleManagement.h"
#include "Position.h"
#include <fstream>
#include <string>
#define SCREEN_LEFT 10
#define SCREEN_RIGHT 110

class Enemy {
protected:
    Position pos;
    int width;
    int height;
    char** shape;
    bool isOutMap;
public:
    Enemy();
    Enemy(Position pos);
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
    ~Enemy();
    
};

class Car: public Enemy {
public:
    Car();
    Car(Position pos);
    string getShapeFile();
};

class Truck: public Enemy {
public:
    Truck();
    Truck(Position pos);
    string getShapeFile();
};

class Bird: public Enemy {
public:
    Bird();
    Bird(Position pos);
    string getShapeFile();
};

class Dinosaur: public Enemy {
public:
    Dinosaur();
    Dinosaur(Position pos);
    string getShapeFile();
};