#include <iostream>
#include <SFML\Graphics.hpp>
#include "Tile.h"
#include "SFMLUtilities.h"

using namespace std;



Tile::Tile(int row, int col, int sideLen, float boardSide,
		sf::RenderWindow * win, bool isEmpty, sf::Color color) : 
		type (Type::NORMAL), window(win) {
	
	if (isEmpty) type = Type::EMPTY;
	else type = Type::NORMAL;

	float sideSize = boardSide / sideLen;
	rect = sf::RectangleShape(sf::Vector2f(sideSize, sideSize));
	rect.setFillColor(color);

	//position and bound
	rect.setPosition(sf::Vector2f(sideSize * col, sideSize * row));
	resetBound();
	setOriginalPos(pos());
	MAX_XY_POS = boardSide - sideSize;
}

void Tile::draw() {
	if (type == Type::EMPTY) return;
	window->draw(rect);
}



sfu::DragNDrop::State Tile::update() {

	if (type == Type::EMPTY) return sfu::DragNDrop::State::DOWN;

	sfu::DragNDrop::State state = dnd.update(rect, *window);
	rect.setPosition(sfu::boundRect(rect, bound));

	return state;
}

bool Tile::shift(sfu::Dir dir) {
	auto newPos = pos() + sfu::vUnit(dir) * size().x;
	if (newPos.x < -1 || newPos.y < -1 || newPos.x > MAX_XY_POS + 1 || newPos.x > MAX_XY_POS + 1)
		return false;
	rect.setPosition(newPos);
	return true;
}

Tile::~Tile() {}
