#include "Map.h"


MAP::MAP(GAME *gm) : width(120), height(35), isPause(0), isEnd(0), player(POSITION(50, 33)), level(LEVEL(1)), game(gm) {
	for (int i = 0; i <= width; ++i) {
		map[0][i] = map[height][i] = '-';
	}
	map[0][width + 1] = map[height][width + 1] = ' ';
	for (int i = 1; i < height; ++i) {
		map[i][0] = map[i][width] = '|';
		if (i % 5 == 0) {
			for (int j = 1; j < width; ++j) {
				map[i][j] = '-';
			}
		}
		else {
			for (int j = 1; j < width; ++j)
				map[i][j] = ' ';
		}
	}
}

MAP::~MAP() {
}

void MAP::drawMap() {
	gotoXY(0, 0);
	for (int i = 0; i <= height; ++i) {
		cout << "  ";
		for (int j = 0; j <= width + 1; ++j)
			cout << map[i][j];
		cout << endl;
	}

	drawRecSingle(130, 1, 40, 20);
	drawRecSingle(130, 24, 40, 10);

	gotoXY(145, 2);
	cout << "INSTRUCTION";
	gotoXY(135, 5);
	cout << "[" << (char)30 << "]: Up";
	gotoXY(135, 7);
	cout << "[" << (char)31 << "]: Down";
	gotoXY(135, 9);
	cout << "[" << (char)16 << "]: Right";
	gotoXY(135, 11);
	wcout << "[" << (char)17 << "]: Left";
	gotoXY(135, 13);
	cout << "[P]: Pause";
	gotoXY(135, 15);
	cout << "[T] Load game";
	gotoXY(135, 17);
	cout << "[S] Save game";


	gotoXY(145, 25);
	cout << "PAUSE PANEL";
	gotoXY(10, 37);
	level.displayLevel();
	cout << "   SPEED: " << level.getSpeed();
}


//To draw any object from its pos, shape, width and height
void MAP::drawObject(POSITION pos, char** shape, int width, int height) {
	for (int i = -height; i < height + 1; i++) {
		gotoXY(pos.getX() - width, pos.getY() + i);
		for (int j = 0; j < 2 * width + 1; j++) {
			cout << shape[i + height][j];
		}
	}
}

void MAP::drawPlayer() {
	player.drawPlayer();
}

void MAP::updatePlayerPos(char key) {
	key = tolower(key);
	switch (key)
	{
	case 'w':	//Up
		player.moveUp();
		break;
	case 's':	//Down
		player.moveDown();
		break;
	case 'd':	//Right
		player.moveRight();
		break;
	case 'a':	//Left
		player.moveLeft();
		break;
	default:
		break;
	}
}

//Initialize new state.
void MAP::newState() {
	system("cls");
	int speed = level.getSpeed();
	int dist = level.getDistance();

	rows.~ROWS();
	new(&rows) ROWS(dist);
	rows.initializeState(speed);
	player.deleteOldPlayer();
	player.setPosition(50, 33);

	drawMap();
	drawPlayer();
}

void MAP::continueGame() {
	system("cls");
	drawMap();
	drawPlayer();
}

//Show/hide pause panel
int MAP::pausePanel() {
	string opt[4] = {
		"1. Continue", "2. Save game", "3. Load game", "4. Back to menu"
	};
	/*
	for (int i = 0; i < 4; ++i) {
		gotoXY(135, 27 + 2 * i);
		cout << opt[i];
	}

	int option = 0;
	gotoXY(135, 27);
	TextColor(11);
	cout << opt[option];
	TextColor(15);

	
	char key;
	while (true) {

		if (_kbhit) {
			key = _getch();
			if (key == 13)
				return option;
			else if (key == 'w' || key == 'W') {
				gotoXY(135, 27 + 2 * option);
				cout << opt[option];
				option--;
				if (option < 0) option = 3;
				gotoXY(135, 27 + 2 * option);
				TextColor(11);
				cout << opt[option];
				TextColor(15);
			}
			else if (key == 's' || key == 'S') {
				gotoXY(135, 27 + 2 * option);
				cout << opt[option];
				option++;
				if (option > 3) option = 0;
				gotoXY(135, 27 + 2 * option);
				TextColor(11);
				cout << opt[option];
				TextColor(15);
			}
		}
	}*/
	int option = returnChoice(opt, 4, 135, 27);
	hidePausePanel(opt, 4, 135, 27);
	return option;
}
void MAP::hidePausePanel(string option[], int length, int x, int y) {
	for (int i = 0; i < length; ++i) {
		gotoXY(x, y + i);
		for (int j = 0; j < option[i].length(); ++j)
			cout << " ";
	}
}

//runGame ver1
void MAP::runGame() {
	int t = 0;
	char key;
	int speed = level.getSpeed();
	int distance = level.getDistance();
	int lightPhase = level.getLightPhase();
	int epoch = level.getEpoch();
	newState();
	while (!isEnd) {
		if (!isPause) {
			rows.newState(t, speed, lightPhase, epoch);
		}
		if (_kbhit()) {
			key = _getch();
			if (key == 27) {
				if (game->backToMenu()) {
					isEnd = true;
					break;
				}
				else continueGame();
			}
			else if (key == 'p' || key == 'P') {
				isPause = true;
				int pauseOption = pausePanel();		//Call Pause panel and return option
				if (pauseOption == 0)
					isPause = false;
				else if (pauseOption == 3) {
					if (game->backToMenu())
						break;
					else {
						continueGame();
						isPause = false;
					}
				}
			}
			else {
				if (!isPause) updatePlayerPos(key);
			}
		}
		if (checkCrash()) {
			player.crashEffect();
			Sleep(1000);
			if (game->printLose()) {
				//Lose and start a new game
				subNewGame();
				replay();
				speed = level.getSpeed();
				distance = level.getDistance();
				lightPhase = level.getLightPhase();
				epoch = level.getEpoch();
			}
			else {
				system("cls");
				drawLoadingBar();
				break;
			}
		}
		t++;
		if (t >= INT_MAX)  //To prevent t from overflow
			t = 0;
		if (player.checkWin()) {			//If user pass level
			system("pause");
			if (game->printCongrat()) {	//Continue playing
				subNewGame();
				levelUp();
				speed = level.getSpeed();
				distance = level.getDistance();
				lightPhase = level.getLightPhase();
				epoch = level.getEpoch();
			}
			else {
				system("cls");
				drawLoadingBar();
				break;
			}
			
		}
	}
}

//runGame ver2
/*
int MAP::runGame() {
	int t = 0;
	char key;
	int speed = level.getSpeed();
	int distance = level.getDistance();
	int lightPhase = level.getLightPhase();
	int epoch = level.getEpoch();
	newState();
	while (!isEnd) {
		if (!isPause) {
			rows.newState(t, speed, lightPhase, epoch);
		}
		if (_kbhit()) {
			key = _getch();
			if (key == 27) {
				isEnd = true;
				return 0;
			}
			else if (key == 'p' || key == 'P') {
				isPause = true;
				int pauseOption = pausePanel();		//Call Pause panel and return option
				if (pauseOption == 0)
					isPause = false;
				else if (pauseOption == 3)
					return 0;;
			}
			else {
				if (!isPause) updatePlayerPos(key);
			}
		}
		if (checkCrash()) {
			player.crashEffect();
			isEnd = true;
			return 2;
		}
		t++;
		if (t >= INT_MAX)  //To prevent t from overflow
			t = 0;
		if (player.checkWin()) {
			system("pause");
			return 1;
		}
	}
}*/

void MAP::levelUp() {
	level.NewLevel();
	newState();
}

void MAP::replay() {
	level.moveToLevel(1);
	newState();
}

bool MAP::checkCrash() {
	vector<int> currentRows;
	player.getCurrentRows(currentRows);
	if (currentRows.empty())
		return false;
	vector<ENEMY*> listEnemies;
	for (int i = 0; i < currentRows.size(); ++i) {
		vector<ENEMY*> temp = rows.listEnemies(currentRows[i]);
		for (int j = 0; j < temp.size(); ++j)
			listEnemies.push_back(temp[j]);
	}
	if (player.checkCrash(listEnemies))
		return true;
	return false;
}

void MAP::saveGame() {
	ofstream ofs;
	string fileName = "Temporary Name"; //temp
	ofs.open(fileName, ios::binary);
	if (!ofs.is_open()) {
		cout << "Cannot create file!\n";
		return;
	}
	player.savePlayer(ofs);
	level.saveLevel(ofs);
	rows.saveRows(ofs);
	ofs.close();
}

void MAP::loadGame() {
	ifstream ifs;
	string fileName = "Temporary Name"; //temp
	ifs.open(fileName, ios::binary);
	if (!ifs.is_open()) {
		cout << "Cannot open file!\n";
		return;
	}
	player.loadPlayer(ifs);
	level.loadLevel(ifs);
	rows.loadRows(ifs, level);
}

