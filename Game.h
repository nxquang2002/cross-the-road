#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include <chrono>
#include <conio.h>
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
};

void drawLoadingBar();
void subNewGame();
void drawInputNameBar();

#endif // !GAME_H_
