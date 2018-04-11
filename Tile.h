#pragma once

#include <cassert>
#include <SFML\Graphics.hpp>

class Tile {
public:

	enum class Type {
		NORMAL,
		EMPTY,
	};

private:

	// Position
	float x;
	float y;
	float sideLen;

	Type type;

	sf::RectangleShape rect;

	sf::RenderWindow * window;

	//void setX(float x) { this->x = x; }
	//void setY(float y) { this->y = y; }

public:
	

	float getX() { return x; }
	float getY() { return y; }

	Type getType() { return type; }

	void draw();

	Tile();
	Tile(bool isEmpty) : type(Type::EMPTY) { assert(isEmpty); }
	Tile(int row, int col, int sideLen, float boardSide, 
		sf::RenderWindow *, sf::Color color);


	~Tile();
};

