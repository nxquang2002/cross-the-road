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
	lightPhase -= 5000;
	epoch -= (epoch / 100) * 20; //epoch = 80% * epoch
}

void LEVEL::moveToLevel(int lvl) {
	if (lvl <= 0 || lvl > 5)
		return;
	nLevel = lvl;
	speed = MIN_SPEED + (lvl-1);					//a little hardcode
	distance = MAX_DISTANCE - (lvl-1);
	lightPhase = MAX_LIGHTPHASE - (lvl - 1) * 5000;
	epoch = MAX_EPOCH * pow(0.8, lvl - 1);
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

bool LEVEL::passAllLevels() {
	return nLevel >= 5;
}

void LEVEL::displayLevel() {
	cout << "LEVEL: " << nLevel;
}

void LEVEL::saveLevel(ofstream& ofs) {
	ofs.write((char*)&nLevel, sizeof(int));
}

void LEVEL::loadLevel(ifstream& ifs) {
	ifs.read((char*)&nLevel, sizeof(int));
	speed = MIN_SPEED + (nLevel - 1);					//a little hardcode
	distance = MAX_DISTANCE - (nLevel - 1);
	lightPhase = MAX_LIGHTPHASE - (nLevel - 1) * 5000;
	epoch = MAX_EPOCH * pow(0.8, nLevel - 1);
}