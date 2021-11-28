#include<iostream>
#include "ConsoleManagement.h"
#include"POSITION.h"
//#include"Player.h"
#include"Enemy.h"

using namespace std;

class MAP {
private:
	int width, height;
	char map[36][125];
	bool isPause;
	bool isEnd;
	//PLAYER player;
public:
	MAP();
	~MAP();

	void drawMap();
	void drawRecSingle(int ox, int oy, short width, short height);
	void drawRecDouble(int ox, int oy, short width, short height);
	void drawObject(POSITION pos, char** shape, int width, int height);
	void updatePlayerPos(char key);
	void newState();
};
