#include "Map.h"

MAP::MAP() : width(120), height(35), isPause(0), isEnd(0) {
	for(int i = 0; i <= width; ++i){
		map[0][i] = map[height][i] = '-';
	}
	map[0][width + 1] = map[height][width + 1] = ' ';
	for(int i = 1; i < height; ++i){
		map[i][0] = map[i][width] = '|';
		if(i % 5 == 0){
			for(int j = 1; j < width; ++j)
				map[i][j] = '-';
		}
		else{
			for(int j = 1; j < width; ++j)
				map[i][j] = ' ';
		}
		if (i % 5 == 2 || i % 5 == 3) {
			map[i][width + 1] = 254;
		}
		else map[i][width + 1] = ' ';
	}
}

MAP::~MAP(){
}

void MAP::drawMap(){
	gotoXY(0, 0);
	for(int i = 0; i <= height; ++i){
		cout << "  ";
		for(int j = 0; j <= width + 1; ++j)
			cout << map[i][j];
		cout << endl;
	}

	drawRecSingle(130, 1, 40, 20);
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

int main(){
	resizeConsole(1300, 700);
	MAP map;
	map.drawMap();

	system("pause");
	return 0;
}