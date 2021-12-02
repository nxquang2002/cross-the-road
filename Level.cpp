#include "Level.h"

LEVEL::LEVEL(int nLevel, int speed, int distance, int lightPhase, int epoch) {
	this->nLevel = nLevel;
	this->speed = speed;
	this->distance = distance;
}

//set tạm sau này điều chỉnh
void LEVEL::NewLevel() {
	nLevel++;
	speed++;
	distance--;
	lightPhase -= 2;
	epoch--;
}
