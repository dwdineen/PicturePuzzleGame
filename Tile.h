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
	float MAX_XY_POS;

	Type type;

	sf::RectangleShape rect;
	sf::RenderWindow * window;

	//For movement:
	sfu::DragNDrop dnd;
	sf::FloatRect bound = sf::FloatRect(0, 0, 5000, 5000);
	
	//originalPos
	sf::Vector2f originalPos;

public:
	sf::Vector2f size() { return rect.getSize(); }
	sf::Vector2f pos() { return rect.getPosition(); }
	sf::Vector2f getOriginalPos() { return originalPos; }
	void setPos(sf::Vector2f vec) { rect.setPosition(vec); }
	void setOriginalPos(sf::Vector2f vec) { originalPos = vec; }
	const sf::RectangleShape getRect() { return rect; }
	

	//float getX() { return rect.getPosition[0]; }
	//float getY() { return rect.getPosition[1]; }

	Type getType() { return type; }

	void draw();
	sfu::DragNDrop::State update();

	bool shift(sfu::Dir dir);
	
	void setBound(sf::FloatRect boundRect) { bound = boundRect; }
	void resetBound() { bound = sf::FloatRect(pos(), size()); }

	Tile(int row, int col, int sideLen, float boardSide, 
		sf::RenderWindow *, bool isEmpty, sf::Color color = sf::Color::White);


	~Tile();
};

