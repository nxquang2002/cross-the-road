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

void LEVEL::saveLevel(ofstream& ofs) {
	ofs.write((char*)&nLevel, sizeof(int));
	ofs.write((char*)&speed, sizeof(int));
	ofs.write((char*)&distance, sizeof(int));
	ofs.write((char*)&lightPhase, sizeof(int));
	ofs.write((char*)&epoch, sizeof(int));
}

void LEVEL::loadLevel(ifstream& ifs) {
	ifs.read((char*)&nLevel, sizeof(int));
	ifs.read((char*)&speed, sizeof(int));
	ifs.read((char*)&distance, sizeof(int));
	ifs.read((char*)&lightPhase, sizeof(int));
	ifs.read((char*)&epoch, sizeof(int));
}