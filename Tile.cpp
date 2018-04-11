#include <iostream>
#include <SFML\Graphics.hpp>
#include "Tile.h"




Tile::Tile() {}

Tile::Tile(int row, int col, int sideLen, float boardSide,
		sf::RenderWindow * win, sf::Color color) {
	
	//Set type
	type = Tile::Type::NORMAL;

	//Set window ptr
	window = win;

	float sideSize = boardSide / sideLen;
	rect = sf::RectangleShape(sf::Vector2f(sideSize, sideSize));
	rect.setFillColor(color);

	x = sideSize * col;
	y = sideSize * row;

	std::cout << x << std::endl;

	rect.setPosition(sf::Vector2f(x, y));

}

void Tile::draw() {
	if (type == Type::EMPTY) return;
	window->draw(rect);
}

Tile::~Tile() {}
