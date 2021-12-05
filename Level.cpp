#include "Level.h"

LEVEL::LEVEL(int nLevel, int speed, int distance, int lightPhase, int epoch) {
	this->nLevel = nLevel;
	this->speed = speed;
	this->distance = distance;
	this->lightPhase = lightPhase;
	this->epoch = epoch;
}

void LEVEL::NewLevel() {
	nLevel++;
	speed++;
	distance--;
	lightPhase -= 2;
	epoch--;
}

int LEVEL::getSpeed() {
	return speed;
}

int LEVEL::getLightPhase() {
	return lightPhase;
}

int LEVEL::getDistance() {
	return distance;
}
