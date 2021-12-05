#include "Map.h"


MAP::MAP() : width(120), height(35), isPause(0), isEnd(0), player(POSITION(50, 33)), level(LEVEL(1)) {
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
}

void MAP::drawRecSingle(int ox, int oy, short width, short height) {
	gotoXY(ox, oy);
	cout << (char)218;				//Top-left corner
	for (int i = 1; i <= width; ++i) {
		cout << (char)196;
	}
	cout << (char)191 << endl;
	gotoXY(ox, ++oy);
	for (int i = 1; i <= height; ++i) {
		cout << (char)179;
		for (int j = 1; j <= width; ++j) {
			cout << " ";
		}
		cout << (char)179 << endl;
		gotoXY(ox, ++oy);
	}

	cout << (char)192;
	for (int i = 1; i <= width; ++i) {
		cout << (char)196;
	}
	cout << (char)217;
}

void MAP::drawRecDouble(int ox, int oy, short width, short height) {
	gotoXY(ox, oy);
	cout << (char)201;					//Top-left corner
	for (int i = 1; i <= width; ++i) {
		cout << (char)205;
	}
	cout << (char)187 << endl;
	gotoXY(ox, ++oy);
	for (int i = 1; i <= height; ++i) {
		cout << (char)186;
		for (int j = 1; j <= width; ++j) {
			cout << " ";
		}
		cout << (char)186 << endl;
		gotoXY(ox, ++oy);
	}

	cout << (char)200;
	for (int i = 1; i <= width; ++i) {
		cout << (char)205;
	}
	cout << (char)188;
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
	switch (key)
	{
	case 72:	//Up
		player.moveUp();
		break;
	case 80:	//Down
		player.moveDown();
		break;
	case 77:	//Right
		player.moveRight();
		break;
	case 75:	//Left
		player.moveLeft();
		break;
	default:
		break;
	}
}


void MAP::newState() {
	char key;
	int speed = level.getSpeed();
	int distance = level.getDistance();
	int lightPhase = level.getLightPhase();
	rows.initializeState(speed);
	drawMap();
	drawPlayer();

	int t = 0;
	while (!isEnd) {
		rows.newState(t, speed, 50000); //time - speed - lightPhase
		if (_kbhit()) {
			key = _getch();
			if (key == 27) {
				break;
			}
			else updatePlayerPos(key);
		}
		if (checkCrash()) {
			player.crashEffect();
			break;
		}
		t++;
		if (t >= INT_MAX)  //To prevent t from overflow
			t = 0;
	}
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


int main(){
	resizeConsole(1300, 700);
	Nocursortype();
 	MAP map;
	map.newState();

 	system("pause");
	return 0;
 }
