#pragma once

#include <cassert>
#include <SFML\Graphics.hpp>
#include "SFMLUtilities.h"

class Tile {
public:

	enum class Type {
		NORMAL,
		EMPTY,
	};

private:

	// Position
	float sideLen;

	Type type;

	sf::RectangleShape rect;
	sf::RenderWindow * window;

	//For movement:
	sfu::DragNDrop dnd;

	sf::Vector2f size() { return rect.getSize(); }
	sf::Vector2f pos() { return rect.getPosition(); }

public:
	

	//float getX() { return rect.getPosition[0]; }
	//float getY() { return rect.getPosition[1]; }

	Type getType() { return type; }

	void draw();
	void update();

	Tile(bool isEmpty, sf::RenderWindow * win) : type(Type::EMPTY), 
		window(win) { assert(isEmpty); }

	Tile(int row, int col, int sideLen, float boardSide, 
		sf::RenderWindow *, sf::Color color);


	~Tile();
};

