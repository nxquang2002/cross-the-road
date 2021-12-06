#ifndef _MAP_H_
#define _MAP_H_

#include<iostream>
#include "ConsoleManagement.h" 
#include"POSITION.h"
#include"Player.h"
#include"Enemy.h"
#include "Rows.h"
#include "Level.h"
#include <thread>
#include<conio.h>
#define _INT_MAX_ 1000000		//To prevent overflow

using namespace std;

class MAP {
private:
	int width, height;
	char map[36][125];
	bool isPause;
	bool isEnd;
	PLAYER player;
	ROWS rows;
	LEVEL level;
public:
	MAP();
	~MAP();

	void drawMap();
	void drawRecSingle(int ox, int oy, short width, short height);
	void drawRecDouble(int ox, int oy, short width, short height);
	void drawObject(POSITION pos, char** shape, int width, int height);
	void drawPlayer();
	void updatePlayerPos(char key);
	void newState();
	bool checkCrash();
};

#endif // !_MAP_H_

