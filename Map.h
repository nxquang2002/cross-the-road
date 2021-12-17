#ifndef _MAP_H_
#define _MAP_H_

#include<iostream>
#include "ConsoleManagement.h" 
#include"POSITION.h"
#include"Player.h"
#include"Enemy.h"
#include "Rows.h"
#include "Level.h"
#include "Game.h"
#include <thread>
#include<conio.h>
#include <fstream>


#define INT_MAX 1000000		//To prevent overflow

using namespace std;

class GAME;

class MAP {
private:
	bool isMute;
	int width, height;
	char map[36][125];
	bool isPause;
	//bool isEnd;
	PLAYER player;
	ROWS rows;
	LEVEL level;
	GAME* game;
public:
	MAP(GAME* gm);
	~MAP();

	void drawMap();
	void drawObject(POSITION pos, char** shape, int width, int height);
	void drawPlayer();
	void updatePlayerPos(char key);
	void newState();
	void loadState();				//After call loadGame(), loadState() for showing stuffs to map.
	bool checkCrash();
	void runGame(bool load);		//Most important function.
	void continueGame();
	int pausePanel();
	void hidePausePanel(string option[], int length, int x, int y);
	void saveGame(bool isExist);	//isExist = true when game is saved before
	void loadGame(string fileName);
	void levelUp();
	void replay();					//Lose and return to level 1
	void setPlayerName(string s);
	bool isSavedBefore();			//If game is loaded, player has name, return true; else return false;
	void setMute(bool mute);
};

#endif // !_MAP_H_