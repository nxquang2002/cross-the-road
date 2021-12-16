#include "Player.h"

PLAYER::PLAYER(POSITION position, bool dead, bool win) {
	pos = position;
	isDead = dead;
	isWin = win;
	name = "";
}

void PLAYER::moveLeft() {
	if (pos.getX() - 1 < SCREEN_LEFT)
		return;
	deleteOldPlayer();
	pos += POSITION(-1, 0);
	drawPlayer();
}

void PLAYER::moveUp() {
	if (pos.getY() - 1 < SCREEN_TOP)
		return;
	deleteOldPlayer();
	pos += POSITION(0, -1);
	drawPlayer();
}

void PLAYER::moveDown() {
	if (pos.getY() + 1 > SCREEN_BOTTOM)
		return;
	deleteOldPlayer();
	pos += POSITION(0, 1);
	drawPlayer();
}

void PLAYER::moveRight() {
	if (pos.getX() + 1 > SCREEN_RIGHT)
		return;
	deleteOldPlayer();
	pos += POSITION(1, 0);
	drawPlayer();
}

bool PLAYER::checkWin() {
	int bot = (pos.getY() + height) / 5 - 1;
	if (bot < 0) {
		isWin = true;
		return true;
	}
	return false;
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

	for (int i = -height; i < height + 1; i++) {
		if ((pos.getY() + i) % 5 == 0 && (pos.getY() + i) <= 35) {
			for (int j = -width; j < width + 1; j++) {
				gotoXY(pos.getX() - j, pos.getY() + i);
				cout << '-';
			}
		}
	}
}

bool PLAYER::isCollide(ENEMY* currentEnemy) {
	if (pos.getX() + width < currentEnemy->getPos().getX() - currentEnemy->getWidth())
		return false;
	if (pos.getX() - width > currentEnemy->getPos().getX() + currentEnemy->getWidth())
		return false;
	if (pos.getY() + height < currentEnemy->getPos().getY() - currentEnemy->getHeight())
		return false;
	if (pos.getY() - height > currentEnemy->getPos().getY() + currentEnemy->getHeight())
		return false;
	return true;
}


bool PLAYER::checkCrash(vector<ENEMY*> enemy) {
	int posX = pos.getX(), posY = pos.getY();
	for (int i = 0; i < enemy.size(); i++) {
		if (isCollide(enemy[i]))
		{
			enemy[i]->enemySound(isMute);
			return true;
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
		if (k < 4) {
			for (int i = -height; i < height + 1; i++) {
				gotoXY(pos.getX() - width, pos.getY() + i);
				for (int j = 0; j < 2 * width + 1; j++) {
					cout << ' ';
				}
			}
			Sleep(100);
		}
	}
}

void PLAYER::getCurrentRows(vector<int>& rows) {
	int top = pos.getY() - height;
	int bot = pos.getY() + height;
	int r1 = top / 5 - 1;
	int r2 = bot / 5 - 1;
	if ((r1 >= 5 && r2 >= 5) || (r1 < 0 && r2 < 0))
		return;
	if (r1 == r2)
		rows.push_back(r1);
	else {
		if (r1 >= 0 && r1 < 5) rows.push_back(r1);
		if (r2 >= 0 && r2 < 5) rows.push_back(r2);
	}
}

void PLAYER::crashEffect() {
	ifstream ifs;
	ifs.open("explosion.txt");

	if (!ifs.is_open()) {
		cout << "Cannot open explosion.txt!\n";
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

	for (int i = 0; i < y; i++)
		delete[] shape[i];
	delete[] shape;
}

void PLAYER::setPosition(int x, int y) {
	pos.setX(x);
	pos.setY(y);
}

void PLAYER::savePlayer(ofstream& ofs) {
	ofs.write((char*)&pos, sizeof(POSITION));
	ofs.write((char*)&isDead, sizeof(bool));
	ofs.write((char*)&isWin, sizeof(bool));
}

void PLAYER::loadPlayer(ifstream& ifs) {
	ifs.read((char*)&pos, sizeof(POSITION));
	ifs.read((char*)&isDead, sizeof(bool));
	ifs.read((char*)&isWin, sizeof(bool));
}

string PLAYER::getName() {
	return name;
}

void PLAYER::setName(string s) {
	name = s;
}
void PLAYER::setMute(bool mute)
{
	isMute = mute;
}