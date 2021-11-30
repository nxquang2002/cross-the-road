#pragma once
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
	//int nEnemy; //lên level thì tăng số lượng enemy? để đây phòng hờ mn ok thì t thêm zô
public:
	LEVEL(int nLevel = 1, int speed = 200, int distance = 7);
	void NewLevel();

};