#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Position.h"
#include "Enemy.h"
#include <string>
#include <vector>
#include <conio.h>
#define SCREEN_LEFT 5
#define SCREEN_RIGHT 120
#define SCREEN_TOP 2
#define SCREEN_BOTTOM 33

class PLAYER {
private:
	POSITION pos;
	bool isDead;
	bool isWin;
	const int width = 1;
	const int height = 1;
	string name;	//For saving game
public:
	PLAYER(POSITION position, bool dead = false, bool win = false);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void drawPlayer();
	void deleteOldPlayer();
	//bool isCollide(int posX, int posY, ENEMY* currentEnemy);
	bool isCollide(ENEMY* currentEnemy);
	bool checkCrash(vector<ENEMY*> enemy);
	void crashEffect();
	void drawEffect(char** shape, int width, int height);
	void getCurrentRows(vector<int>& rows); //Get rows index, where player are standing
	bool checkWin();
	void setPosition(int x, int y);
	void savePlayer(ofstream& ofs);
	void loadPlayer(ifstream& ifs);;
	string getName();
	void setName(string s);
};

#endif // !_PLAYER_H_