#include "Enemy.h"

Enemy::Enemy() {
    this->width = 0;
    this->height = 0;
    this->shape = nullptr;
    this->isOutMap = 1;
}

Enemy::Enemy(Position pos) {
    this->pos = pos;
    this->width = 0;
    this->height = 0;
    this->shape = nullptr;
    this->isOutMap = 1;
}

int Enemy::getWidth() {
    return width;
}

int Enemy::getHeight() {
    return height;
}

char** Enemy::getShape() {
    ifstream ifs;
    ifs.open(this->getShapeFile());
    
    if (!ifs.is_open()) {
        cout << "Cannot open car.txt!\n";
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
        for (int j = 0; j < x; j++) {
            shape[i][j] = s[j];
            //cout << tmp[i][j];
        }
        //cout << "\n";
    }
    ifs.close();

    return shape;
}

void Enemy::drawShape() {
    for (int i = -height; i < height + 1; i++) {
        gotoXY(pos.getX() - width, pos.getY() + i);
        int j = 0, tmp;
        if (pos.getX() + width > SCREEN_RIGHT)
            tmp = width + 1;
        else if (pos.getX() - width > SCREEN_LEFT) {

        }
        else
            tmp = 2 * width + 1;
        for (int j = 0; j < tmp; j++) {
                cout << shape[i + height][j];
            }
    }
}
    
Position Enemy::getPos() {
    return pos;
}

void Enemy::sound() {

    //implement

    return;
}

bool Enemy::isOutOfMap() {
    if (pos.getX() - width < SCREEN_LEFT || pos.getX() + width > SCREEN_RIGHT)
        return true;
    return false;
}

bool Enemy::move() {
    if (isOutOfMap())
        return false;
    this->pos += Position(3 * width, 0);
    return true; 
}

void Enemy::deleteOldEnemy() {

    for (int i = -height; i < height + 1; i++) {
        gotoXY(pos.getX() - width, pos.getY() + i);
        for (int j = 0; j < 2 * width + 1; j++) {
            cout << ' ';
        }
    }
}

Enemy::~Enemy() {
    for (int i = 0; i < height * 2 + 1; i++)
        delete[] shape[i];
    delete[] shape;
}

Car::Car(): Enemy() {}

Car::Car(Position pos): Enemy(pos) {}

string Car::getShapeFile() {
    return "car.txt";
}

Truck::Truck(): Enemy() {}

Truck::Truck(Position pos): Enemy(pos) {}

string Truck::getShapeFile() {
    return "truck.txt";
}

Bird::Bird(): Enemy() {}

Bird::Bird(Position pos): Enemy(pos) {}

string Bird::getShapeFile() {
    return "bird.txt";
}

Dinosaur::Dinosaur(): Enemy() {}

Dinosaur::Dinosaur(Position pos): Enemy(pos) {}

string Dinosaur::getShapeFile() {
    return "dino.txt";
}

int main()
{
    Enemy* e = new Dinosaur(Position(25, 10));
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