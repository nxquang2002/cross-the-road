#include "Level.h"

LEVEL::LEVEL(int nLevel, int speed, int distance) {
	this->nLevel = nLevel;
	this->speed = speed;
	this->distance = distance;
}

//set tạm sau này điều chỉnh
void LEVEL::NewLevel() {
	nLevel++;
	speed -= 10;
	distance--;
}
