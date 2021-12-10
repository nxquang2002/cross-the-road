#include "Enemy.h"

ENEMY::ENEMY() {
    this->width = 0;
    this->height = 0;
    this->shape = nullptr;
    this->isOutMap = true;
    this->speed = 0;
}

ENEMY::ENEMY(POSITION pos, bool right, int spd) {
    this->pos = pos;
    this->width = 0;
    this->height = 0;
    this->speed = spd;
    this->shape = nullptr;
    this->isOutMap = true;
    this->dirRight = right;   
}

int ENEMY::getWidth() {
    return width;
}

int ENEMY::getHeight() {
    return height;
}

char** ENEMY::getShape() {
    ifstream ifs;
    ifs.open(this->getShapeFile());

    if (!ifs.is_open()) {
        cout << "Cannot open " << this->getShapeFile() << "!\n";
        return nullptr;
    }

    int x, y;
    ifs >> x >> y;

    width = x / 2;
    height = y / 2;

    shape = new char* [y];
    for (int i = 0; i < y; i++)
        shape[i] = new char[x];

    string s;
    getline(ifs, s, '\n');
    for (int i = 0; i < y; i++) {
        getline(ifs, s, '\n');
        for (int j = 0; j < x; j++)
            shape[i][j] = s[j];
    }

    ifs.close();
    return shape;
}

void ENEMY::setSpeed(int spd) {
    speed = spd;
}

void ENEMY::drawShape() {
    for (int i = -height; i < height + 1; i++)
    {
        int startX, endX;
        if (pos.getX() + width > SCREEN_RIGHT)
        {
            startX = width;
            endX = SCREEN_RIGHT - pos.getX();
        }
        else if (pos.getX() - width < SCREEN_LEFT) {
            startX = pos.getX() - SCREEN_LEFT;
            endX = width;
        }
        else
        {
            startX = width;
            endX = width;
        }
        gotoXY(pos.getX() - startX, pos.getY() + i);
        for (int j = -startX; j < endX + 1; j++)
        {
            cout << shape[i + height][j + width];
        }
    }
}

POSITION ENEMY::getPos() {
    return pos;
}

void ENEMY::sound() {

    //implement

    return;
}

bool ENEMY::isOutOfMap() {
    if (pos.getX() + width < SCREEN_LEFT || pos.getX() - width > SCREEN_RIGHT)
        isOutMap = true; //what does this var do?
    else
        isOutMap = false;
    return isOutMap;
}

bool ENEMY::move() {
    if (isOutOfMap())
        return false;
    if (dirRight)
        this->pos += speed;
    else
        this->pos -= speed;
    return true;
}

void ENEMY::deleteOldEnemy() {

    for (int i = -height; i < height + 1; i++)
    {
        int startX, endX;
        if (pos.getX() + width > SCREEN_RIGHT)
        {
            startX = width;
            endX = SCREEN_RIGHT - pos.getX();
        }
        else if (pos.getX() - width < SCREEN_LEFT) {
            startX = pos.getX() - SCREEN_LEFT;
            endX = width;
        }
        else
        {
            startX = width;
            endX = width;
        }
        gotoXY(pos.getX() - startX, pos.getY() + i);
        for (int j = -startX; j < endX + 1; j++)
        {
            cout << ' ';
        }
    }
}

ENEMY::~ENEMY() {
    for (int i = 0; i < height * 2 + 1; i++)
        delete[] shape[i];
    delete[] shape;
}

Car::Car() : ENEMY() {}

Car::Car(POSITION pos, bool dirRight, int spd) : ENEMY(pos, dirRight, spd) {}

string Car::getShapeFile() {
    if (dirRight)
        return "car1.txt";
    return "car.txt";
}

Truck::Truck() : ENEMY() {}

Truck::Truck(POSITION pos, bool dirRight, int spd) : ENEMY(pos, dirRight, spd) {}

string Truck::getShapeFile() {
    if (dirRight)
        return "truck1.txt";
    return "truck.txt";
}

Bird::Bird() : ENEMY() {}

Bird::Bird(POSITION pos, bool dirRight, int spd) : ENEMY(pos, dirRight, spd) {}

string Bird::getShapeFile() {
    if (dirRight)
        return "bird1.txt";
    return "bird.txt";
}

Dinosaur::Dinosaur() : ENEMY() {}

Dinosaur::Dinosaur(POSITION pos, bool dirRight, int spd) : ENEMY(pos, dirRight, spd) {}

string Dinosaur::getShapeFile() {
    if (dirRight)
        return "dino1.txt";
    return "dino.txt";
}

void ENEMY::saveEnemy(ofstream& ofs) {
    ofs.write((char*)&pos, sizeof(POSITION));
     ofs.write((char*)&width, sizeof(int));
}

