#include "Player.h"

PLAYER::PLAYER(POSITION position, bool dead, bool win) {
	pos = position;
	isDead = dead;
	isWin = win;
}

void PLAYER::moveLeft() {
	deleteOldPlayer();
	pos += POSITION(-1, 0);
	drawPlayer();
}

void PLAYER::moveUp() {
	deleteOldPlayer();
	pos += POSITION(0, -1);
	drawPlayer();
}

void PLAYER::moveDown() {
	deleteOldPlayer();
	pos += POSITION(0, 1);
	drawPlayer();
}

void PLAYER::moveRight() {
	deleteOldPlayer();
	pos += POSITION(1, 0);
	drawPlayer();
}

void PLAYER::drawPlayer() {
	string shape[] = {
		" o ",
		"/|\\",
		"/ \\" };
	for (int i = -height; i < height + 1; i++) {
		gotoXY(pos.getX() - width, pos.getY() + i);
		for (int j = 0; j < 2 * width + 1; j++) {
			cout << shape[i + height][j];
		}
	}
}

void PLAYER::deleteOldPlayer() {
	for (int i = -height; i < height + 1; i++) {
		gotoXY(pos.getX() - width, pos.getY() + i);
		for (int j = 0; j < 2 * width + 1; j++) {
			cout << ' ';
		}
	}
}

bool PLAYER::isCollide(int posX, int posY, Enemy* currentEnemy) {
	if (posX >= currentEnemy->getPos().getX() - currentEnemy->getWidth() &&
		posX <= currentEnemy->getPos().getX() + currentEnemy->getWidth() &&
		posY >= currentEnemy->getPos().getY() - currentEnemy->getHeight() &&
		posY <= currentEnemy->getPos().getY() + currentEnemy->getHeight())
		return true;

	return false;
}

bool PLAYER::checkCrash(vector<Enemy*> enemy) {
	int posX = pos.getX(), posY = pos.getY();
	for (int i = 0; i < enemy.size(); i++) {
		for (int k = -width; k < width + 1; k++) {
			if (isCollide(posX + k, posY + 1, enemy[i])) return true;
		}
	}
	return false;
}

void PLAYER::drawEffect(char** shape, int width, int height) {
	deleteOldPlayer();
	for (int k = 0; k < 5; k++) {
		for (int i = -height; i < height + 1; i++) {
			gotoXY(pos.getX() - width, pos.getY() + i);
			for (int j = 0; j < 2 * width + 1; j++) {
				cout << shape[i + height][j];
			}
		}
		Sleep(100);
		for (int i = -height; i < height + 1; i++) {
			gotoXY(pos.getX() - width, pos.getY() + i);
			for (int j = 0; j < 2 * width + 1; j++) {
				cout << ' ';
			}
		}
		Sleep(100);
		
	}
}

void PLAYER::crashEffect() {
	ifstream ifs;
	ifs.open("explosion.txt");

	if (!ifs.is_open()) {
		cout << "Cannot open car.txt!\n";
		return;
	}

	int x, y;
	ifs >> x >> y;
	char** shape;
	int width = x / 2;
	int height = y / 2;
	shape = new char* [y];
	for (int i = 0; i < y; i++)
		shape[i] = new char[x];

	string s;
	getline(ifs, s, '\n');
	for (int i = 0; i < y; i++) {
		getline(ifs, s, '\n');
		for (int j = 0; j < x; j++) {
			shape[i][j] = s[j];
		}
	}
	ifs.close();
	drawEffect(shape, width, height);

}
