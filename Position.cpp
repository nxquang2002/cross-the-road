#include "Position.h"

Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}

int Position::getX() { return x; }
int Position::getY() { return y; }

Position Position::operator+(const Position& p) {
	Position tmp(x, y);
	tmp.x += p.x;
	tmp.y += p.y;
	return tmp;
}

Position Position::operator-(const Position& p) {
	Position tmp(x, y);
	tmp.x -= p.x;
	tmp.y -= p.y;
	return tmp;
}

Position& Position::operator+=(const Position& a) {
	*this = *this + a;
	return *this;
}

Position& Position::operator-=(const Position& a) {
	*this = *this + a;
	return *this;
}


int Position::Distance(const Position& p) {
	return sqrt((p.x - x) * (p.x - x) / (3 * 3) + (p.y - y) * (p.y - y));
}