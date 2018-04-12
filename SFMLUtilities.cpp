#include <SFML\Graphics.hpp>
#include "SFMLUtilities.h"

bool sfu::mouseClickedOnRectShape(const sf::RectangleShape & rect, const sf::RenderWindow & win) {
	sf::Vector2f mousePos(sf::Mouse::getPosition(win));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (sf::FloatRect(rect.getPosition(),
			rect.getSize()).contains(mousePos)) {
			return true;
		}
	}
	return false;
}

sf::Vector2f sfu::mousePosf(const sf::RenderWindow & win) {
	return sf::Vector2f(sf::Mouse::getPosition(win));
}

sfu::DragNDrop::State sfu::DragNDrop::update
	(sf::RectangleShape & rect, const sf::RenderWindow & win) {

	//If not clicking
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		isBeingMoved = false;
		if (lastState != State::DOWN) { lastState = State::DOWN; return State::LOWERED; } else { lastState = State::DOWN; return State::DOWN; }
	}

	//If clicking but not set to being moved
	else if (!isBeingMoved) {
		if (sfu::mouseClickedOnRectShape(rect, win)) {
			isBeingMoved = true;
			mouseRelation = sfu::mousePosf(win) - rect.getPosition();
		}
		if (lastState != State::DOWN) { lastState = State::DOWN; return State::LOWERED; } else { lastState = State::DOWN; return State::DOWN; }
	}

	//If set to being moved
	if (isBeingMoved) {
		auto newPos = sf::Vector2f((sf::Mouse::getPosition(win))) - mouseRelation;
		rect.setPosition(newPos);
		if (lastState != State::UP) { lastState = State::UP; return State::RAISED; } else { lastState = State::UP; return State::UP; }
	}

	//Else not being moved
	if (lastState != State::DOWN) { lastState = State::DOWN; return State::LOWERED; } else { lastState = State::DOWN; return State::DOWN; }
}