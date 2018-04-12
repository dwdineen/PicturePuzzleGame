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

sf::Vector2f sfu::boundRect(const sf::RectangleShape & rect, const sf::FloatRect & bound) {
	
	sf::Vector2f returnVec = rect.getPosition();
	auto x = returnVec.x;
	auto y = returnVec.y;
	if (rect.getPosition().x < bound.left) returnVec = (sf::Vector2f(bound.left, y));
	if (rect.getPosition().y < bound.top) returnVec = (sf::Vector2f(returnVec.x, bound.top));
	if (rect.getPosition().x + rect.getSize().x > bound.left + bound.width)
		returnVec = (sf::Vector2f(bound.left + bound.width - rect.getSize().x, returnVec.y));
	if (rect.getPosition().y + rect.getSize().y > bound.top + bound.height)
		returnVec = (x, sf::Vector2f(returnVec.x, bound.top + bound.height- rect.getSize().y));

	return returnVec;
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