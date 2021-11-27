#include "Enemy.h"

ENEMY::ENEMY() {
    this->width = 0;
    this->height = 0;
    this->shape = nullptr;
    this->isOutMap = true;
}

ENEMY::ENEMY(POSITION pos) {
    this->pos = pos;
    this->width = 0;
    this->height = 0;
    this->shape = nullptr;
    this->isOutMap = true;
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

    shape = new char*[y];
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
        for (int j = - startX; j < endX + 1; j++) 
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
    this->pos += POSITION(3 * width, 0);
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
        for (int j = - startX; j < endX + 1; j++) 
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

Car::Car(): ENEMY() {}

Car::Car(POSITION pos): ENEMY(pos) {}

string Car::getShapeFile() {
    return "car.txt";
}

Truck::Truck(): ENEMY() {}

Truck::Truck(POSITION pos): ENEMY(pos) {}

string Truck::getShapeFile() {
    return "truck.txt";
}

Bird::Bird(): ENEMY() {}

Bird::Bird(POSITION pos): ENEMY(pos) {}

string Bird::getShapeFile() {
    return "bird.txt";
}

Dinosaur::Dinosaur(): ENEMY() {}

Dinosaur::Dinosaur(POSITION pos): ENEMY(pos) {}

string Dinosaur::getShapeFile() {
    return "dino.txt";
}

int main()
{
    ENEMY* e = new Dinosaur(POSITION(25, 10));
    e->getShape();
    e->drawShape();
    Sleep(500);
    for (int i = 0; i < 10; i++) {
        e->deleteOldEnemy();
        Sleep(200);
        e->move();
        e->drawShape();
        Sleep(200);
    }
    system("pause");
    return 0;
}