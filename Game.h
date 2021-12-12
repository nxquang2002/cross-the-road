#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include <chrono>
#include <conio.h>
#include "Map.h"
#include "ConsoleManagement.h"

#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define SPACE 32
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

class GAME {
public:
	void newGame();
	void menu();
	void title();
	void levelUp();
	void setting();
	bool printCongrat();
	int returnChoice(string menu[], const int length, int x, int y);
	bool printLose();
	bool saveGameMenu();
	bool backToMenu();
private:
	MAP map;
};

void drawLoadingBar();
void subNewGame();
void drawInputNameBar();

#endif // !GAME_H_
 
