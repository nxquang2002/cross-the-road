#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <iostream>


using namespace std;

class LEVEL {
private:
	int nLevel;
	int speed;
	int distance;
	int lightPhase;
	int epoch;
public:
	LEVEL(int nLevel = 1, int speed = 2, int distance = 7, int lightPhase = 50000, int epoch = 1000);
	void NewLevel();
	int getSpeed();
	int getDistance();
	int getLightPhase();
	int getEpoch();

	void displayLevel();
};

#endif
