#ifndef _POSITION_H_
#define _POSITION_H_

#include <iostream>
#include <cmath>
using namespace std;

class POSITION {
private:
	int x, y;
public:
	POSITION(int x = 0, int y = 0);

	int getX();
	int getY();
	void setX(int _x);
	void setY(int _y);

	POSITION operator+(const POSITION& p);
	POSITION operator-(const POSITION& p);
	POSITION& operator+=(const POSITION& a);
	POSITION& operator-=(const POSITION& a);

	int Distance(const POSITION& p);
};

#endif
