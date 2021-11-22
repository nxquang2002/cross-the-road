#pragma once
#include <iostream>
using namespace std;

class Position {
private:
	int x, y;
public:
	Position(int x = 0, int y = 0);

	int getX();
	int getY();

	Position operator+(const Position& p);
	Position operator-(const Position& p);
	Position& operator+=(const Position& a);
	Position& operator-=(const Position& a);

	int Distance(const Position& p);
};