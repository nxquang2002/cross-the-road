#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Position.h"
#include "Enemy.h"
#include <string>
#include <vector>
#include <conio.h>

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
};

#endif // !_PLAYER_H_