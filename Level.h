#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
#define MAX_LEVEL 5
#define MIN_SPEED 2	
#define MAX_DISTANCE 7
#define MAX_LIGHTPHASE 50000
#define MAX_EPOCH 1000

class LEVEL {
private:
	int nLevel;
	int speed;
	int distance;
	int lightPhase;
	int epoch;
public:
	LEVEL(int nLevel = 1, int speed = MIN_SPEED, int distance = MAX_DISTANCE, int lightPhase = MAX_LIGHTPHASE, int epoch = MAX_EPOCH);
	void NewLevel();
	void moveToLevel(int lvl);
	int getSpeed();
	int getDistance();
	int getLightPhase();
	int getEpoch();
	int getLevel();
	bool passAllLevels();
	void displayLevel();
	void saveLevel(ofstream& ofs);
	void loadLevel(ifstream& ifs);
};

#endif