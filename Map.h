#include<iostream>
#include "ConsoleManagement.h"
#include"Position.h"
#include"Enemy.h"


using namespace std;

class MAP{
private:
	int width, height;
	char map[36][125];
	bool isPause;
	bool isEnd;
public:
	MAP();
	~MAP();

	void drawMap();
	void drawRecSingle(int ox, int oy, short width, short height);
	void drawRecDouble(int ox, int oy, short width, short height);
	void drawObject(Position pos, char** shape, int width, int height);

};
