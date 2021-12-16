#include "Map.h"


MAP::MAP(GAME* gm) : width(120), height(35), isPause(0), player(POSITION(50, 33)), level(LEVEL(1)), game(gm), rows(ROWS(7)) {
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
	for (int i = 0; i < 5; ++i) {
		gotoXY(123, 3 + 5 * (i + 1));
		TextColor(10);          //Draw the light
		cout << (char)254;
		TextColor(15);
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
	cout << "[L] Save game";


	gotoXY(145, 25);
	cout << "PAUSE PANEL";
	gotoXY(10, 37);
	level.displayLevel();
	cout << "   SPEED: " << level.getSpeed();
	gotoXY(10, 39);
	cout << "PLAYER: " << player.getName();
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

void MAP::setPlayerName(string s) {
	player.setName(s);
}

void MAP::loadState() {
	system("cls");
	player.deleteOldPlayer();

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
	gotoXY(135, 15);
	cout << "             ";
	gotoXY(135, 17);
	cout << "               ";
	int option = returnChoice(opt, 4, 135, 27);
	hidePausePanel(opt, 4, 135, 27);
	return option;
}
void MAP::hidePausePanel(string option[], int length, int x, int y) {
	for (int i = 0; i < length; ++i) {
		gotoXY(x, y + 2 * i);
		for (int j = 0; j < option[i].length(); ++j)
			cout << " ";
	}
	gotoXY(135, 15);
	cout << "[T] Load game";
	gotoXY(135, 17);
	cout << "[L] Save game";
}

//runGame ver1
void MAP::runGame() {
	int t = 0;
	char key;
	int speed = level.getSpeed();
	int distance = level.getDistance();
	int lightPhase = level.getLightPhase();
	int epoch = level.getEpoch();
	gameSound(isMute);								// start sound when game run
	newState();
	while (true) {
		if (!isPause) {
			rows.newState(t, speed, lightPhase, epoch);
		}
		if (_kbhit()) {
			key = _getch();
			if (key == 27) {
				int back = game->backToMenu();
				if (back == 0 || back == 1) {
					//Back with or without save
					system("cls");
					drawLoadingBar();
					break;
				}
				else continueGame();				//Cancel
			}
			else if (key == 'p' || key == 'P') {
				isPause = true;
				int pauseOption = pausePanel();		//Call Pause panel and return option
				if (pauseOption == 0)
					isPause = false;
				else if (pauseOption == 3) {
					int back = game->backToMenu();
					if (back == 0 || back == 1) {
						system("cls");
						drawLoadingBar();
						break;
					}
					else {
						continueGame();
						isPause = false;
					}
				}
			}
			else if (key == 'l' || key == 'L') {
				if (game->saveGameMenu()) {
					system("cls");
					saveGame();
					drawLoadingBar();
				}
				continueGame();
			}
			else if (key == 't' || key == 'T') {
				game->loadGame();
				system("cls");
				subNewGame();
				system("cls");
				loadState();
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
				gameSound(isMute);				// restart sound when replay
				replay();	//return to level 1
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
		if (t >= INT_MAX)					//To prevent t from overflow
			t = 0;
		if (player.checkWin()) {			//If user pass level
			system("pause");
			if (level.passAllLevels()) {	//If player pass all level, return menu.
				game->printCongrat();
				system("cls");
				drawLoadingBar();
				break;
			}
			if (game->levelUp()) {			//Continue playing
				subNewGame();
				gameSound(isMute);			// restart sound when new level
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

void MAP::levelUp() {
	level.NewLevel();
	newState();
}

void MAP::replay() {
	level.moveToLevel(1);
	newState();
}

bool MAP::checkCrash() {
	//Get enemy of rows where player is standing and check collision.
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
	string path = "SaveGame/";

	//A text file stores all names of saved file.
	ofs.open(path + "SaveGameFileName.txt", ios::app);
	if (!ofs.is_open()) {
		cout << "Cannot create file!\n";
		system("pause");
		ofs.close();
		return;
	}
	ofs << player.getName() << "\n";
	ofs.close();


	ofs.open(path + player.getName() + ".dat", ios::binary);
	if (!ofs.is_open()) {
		cout << "Cannot create file!\n";
		ofs.close();
		system("pause");
		return;
	}
	player.savePlayer(ofs);
}


void MAP::loadGame(string fileName) {
	rows.~ROWS();
	new(&rows) ROWS();

	ifstream ifs;
	ifs.open(fileName, ios::binary);
	if (!ifs.is_open()) {
		cout << "Cannot open file!\n";
		return;
	}
	player.loadPlayer(ifs);
	level.loadLevel(ifs);
	rows.loadRows(ifs, level);
	ifs.close();
}
void MAP::setMute(bool mute)
{
	isMute = mute;
	player.setMute(mute);
}
