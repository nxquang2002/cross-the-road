#include "Level.h"

LEVEL::LEVEL(int nLevel, int speed, int distance, int lightPhase, int epoch) {
	this->nLevel = nLevel;
	this->speed = speed;
	this->distance = distance;
	this->lightPhase = lightPhase;
	this->epoch = epoch;
}

void LEVEL::NewLevel() {
	if (nLevel == 5)
		return;
	nLevel++;
	speed++;
	distance--;
	lightPhase -= 10000;
	epoch -= (epoch / 100) * 20;
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

int LEVEL::getEpoch() {
	return epoch;
}

void LEVEL::displayLevel() {
	cout << "LEVEL: " << nLevel;
}
