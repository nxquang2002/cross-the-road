#include "Position.h"

POSITION::POSITION(int x, int y) {
	this->x = x;
	this->y = y;
}

int POSITION::getX() { return x; }
int POSITION::getY() { return y; }
void POSITION::setX(int _x) { x = _x; }
void POSITION::setY(int _y) { y = _y; }

POSITION POSITION::operator+(const POSITION& p) {
	POSITION tmp(x, y);
	tmp.x += p.x;
	tmp.y += p.y;
	return tmp;
}

POSITION POSITION::operator-(const POSITION& p) {
	POSITION tmp(x, y);
	tmp.x -= p.x;
	tmp.y -= p.y;
	return tmp;
}

POSITION& POSITION::operator+=(const POSITION& a) {
	*this = *this + a;
	return *this;
}

POSITION& POSITION::operator-=(const POSITION& a) {
	*this = *this + a;
	return *this;
}


int POSITION::Distance(const POSITION& p) {
	return sqrt((p.x - x) * (p.x - x) / (3 * 3) + (p.y - y) * (p.y - y));
}
