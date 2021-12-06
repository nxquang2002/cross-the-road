#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Position.h"
#include "Enemy.h"
#include <string>
#include <vector>
#include <conio.h>
#define SCREEN_LEFT 10 //used to be 5, fix to 10 due to warning
#define SCREEN_RIGHT 110 //used to be 120, fix to 10 due to warning
#define SCREEN_TOP 2
#define SCREEN_BOTTOM 33

class PLAYER {
private:
	POSITION pos;
	bool isDead;
	bool isWin;
	const int width = 1;
	const int height = 1;
public:
	PLAYER(POSITION position, bool dead = false, bool win = false);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void drawPlayer();
	void deleteOldPlayer();
	bool isCollide(int posX, int posY, ENEMY* currentEnemy);
	bool checkCrash(vector<ENEMY*> enemy);
	void crashEffect();
	void drawEffect(char** shape, int width, int height);
	void getCurrentRows(vector<int> &rows); //Get rows index, where player are standing

	bool isCollide(ENEMY* currentEnemy);
};

#endif // !_PLAYER_H_