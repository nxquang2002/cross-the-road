#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include <chrono>
#include <conio.h>
#include "Map.h"
#include "ConsoleManagement.h"
#pragma comment (lib, "winmm.lib")

#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define SPACE 32
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;
class MAP;

class GAME {
public:
	GAME();
	~GAME();
	void newGame();
	void loadGame();
	void loadGameMenu(vector<string>& fileName, bool& noSaveGame, int& startX, int& startY, string& path, int& option, int& maxFile);
	void menu();
	void title();
	bool levelUp();
	void setting();
	//void setting2();			// add sound to setting
	void printCongrat();
	bool printLose();
	void inputSaveGameName();
	bool saveGameMenu();
	int backToMenu();
private:
	MAP* map;
	string gameName;
	bool isMute = false;
};

void drawLoadingBar();
void subNewGame();
void drawInputNameBar();
int returnChoice(string menu[], const int length, int x, int y);

// mute ON/OFF soundwhe choice
int returnChoice2(bool mute, string menu[], const int length, int x, int y);

void drawRecSingle(int ox, int oy, short width, short height);
void drawRecDouble(int ox, int oy, short width, short height);
void gameSound(bool mute);
void clickSound(bool mute);
void chooseSound(bool mute);
void keyboardSound(bool mute);

#endif
