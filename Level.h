#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <iostream>
#include "Enemy.h"
#include "Player.h"
#include "Position.h"
#include "Map.h"
#include "SingleRow.h"

using namespace std;

class LEVEL {
private:
	int nLevel;
	int speed;
	int distance;
	int lightPhase;
	int epoch;
public:
	LEVEL(int nLevel = 1, int speed = 2, int distance = 7, int lightPhase = 20, int epoch = 5);
	void NewLevel();

};

#endif
