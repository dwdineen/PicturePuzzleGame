#include <iostream>
#include <SFML\Graphics.hpp>
#include "Tile.h"
#include "SFMLUtilities.h"

using namespace std;



Tile::Tile(int row, int col, int sideLen, float boardSide,
		sf::RenderWindow * win, sf::Color color) : 
		type (Type::NORMAL), window(win) {
	
	float sideSize = boardSide / sideLen;
	rect = sf::RectangleShape(sf::Vector2f(sideSize, sideSize));
	rect.setFillColor(color);

	rect.setPosition(sf::Vector2f(sideSize * col, sideSize * row));

}

void Tile::draw() {
	if (type == Type::EMPTY) return;
	window->draw(rect);
}



void Tile::update() {

	dnd.update(rect, *window);
	rect.setPosition(sfu::boundRect(rect, sf::FloatRect(sf::Vector2f(30, 30), sf::Vector2f(300, 300))));

}

Tile::~Tile() {}
