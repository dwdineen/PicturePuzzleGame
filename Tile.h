#pragma once

#include <cassert>

class Tile {

public:

	enum Type {
		NORMAL,
		EMPTY,
	};

private:

	double x;
	double y;

	Type type;

	//void setX(double x) { this->x = x; }
	//void setY(double y) { this->y = y; }

public:
	

	double getX() { return x; }
	double getY() { return y; }

	Type getType() { return type; }

	Tile();
	Tile(bool isEmpty) : type(Type::EMPTY) { assert(isEmpty); }
	~Tile();
};

