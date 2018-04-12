#include <SFML\Graphics.hpp>
#include <iostream>
#include "SFMLUtilities.h"

sf::Vector2f sfu::vUnit(Dir dir) {
	switch (dir) {
	case Dir::UP: return sf::Vector2f(0, -1);
	case Dir::DOWN: return sf::Vector2f(0, 1);
	case Dir::RIGHT: return sf::Vector2f(1, 0);
	case Dir::LEFT: return sf::Vector2f(-1, 0);
	}
}

sfu::Dir sfu::getDirAtoB(const sf::Vector2f & A, const sf::Vector2f & B) {
	float xDiff = B.x - A.x;
	float yDiff = B.y - A.y;
	if (std::abs(xDiff) > std::abs(yDiff)) {
		if (xDiff > 0) return Dir::RIGHT;
		else return Dir::LEFT;
	} else if (std::abs(xDiff) < std::abs(yDiff)) {
		if (yDiff > 0) return Dir::DOWN;
		else return Dir::UP;
	}

	std::cout << xDiff << " " << yDiff << std::endl;

	throw "SamePoint";
}

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

sf::FloatRect sfu::concatRects(const sf::RectangleShape & rect1, const sf::RectangleShape & rect2) {
	return concatRects(sf::FloatRect(rect1.getPosition(), rect1.getSize()), 
		sf::FloatRect(rect2.getPosition(), rect2.getSize()));
}

sf::FloatRect sfu::concatRects(const sf::FloatRect & rect1, const sf::FloatRect & rect2) {
	float x1 = rect1.left, y1 = rect1.top;
	float x2 = rect2.left + rect2.width, y2 = rect2.top + rect2.height;
	float w = x2 - x1, h = y2 - y1;
	return sf::FloatRect(x1, y1, w, h);
}

bool sfu::rectsClose(const sf::RectangleShape & a, const sf::RectangleShape & b, float delta) {
	return pointsClose(a.getPosition(), b.getPosition(), delta);
}

bool sfu::pointsClose(const sf::Vector2f & a, const sf::Vector2f & b, float delta) {
	if (std::abs(a.x - b.x) < delta && std::abs(a.y - b.y) < delta) return true;
	return false;
}

sfu::DragNDrop::State sfu::DragNDrop::update
	(sf::RectangleShape & rect, const sf::RenderWindow & win) {

	State state = State::DOWN;

	bool isClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	if (isClick) {
		
		if (tileUpLastFrame) {
			auto newPos = sf::Vector2f((sf::Mouse::getPosition(win))) - mouseRelation;
			rect.setPosition(newPos);
			state = State::UP;

		} else {
			if (mouseClickedLastFrame || !sfu::mouseClickedOnRectShape(rect, win)) {
				tileUpLastFrame = false;
				state = State::DOWN;
			} else {
				tileUpLastFrame = true;
				mouseRelation = sfu::mousePosf(win) - rect.getPosition();
				auto newPos = sf::Vector2f((sf::Mouse::getPosition(win))) - mouseRelation;
				rect.setPosition(newPos);
				state = State::RAISED;
			}
		}

		mouseClickedLastFrame = true;

	} else {

		state = (tileUpLastFrame) ? State::LOWERED : State::DOWN;

		tileUpLastFrame = false;
		mouseClickedLastFrame = false;
	}




	////If not clicking
	//if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	//	isBeingMoved = false;
	//	state = (tileUpLastFrame) ? State::LOWERED : State::DOWN;

	//	tileUpLastFrame == false;
	//	mouseClickedLastFrame == false;
	//}

	////If clicking but not set to being moved
	//else if (!isBeingMoved && !mouseClickedLastFrame) {
	//	if (sfu::mouseClickedOnRectShape(rect, win)) {
	//		isBeingMoved = true;
	//		mouseRelation = sfu::mousePosf(win) - rect.getPosition();
	//		state = State::RAISED;
	//		auto newPos = sf::Vector2f((sf::Mouse::getPosition(win))) - mouseRelation;
	//		rect.setPosition(newPos);

	//		//Last frame:
	//		tileUpLastFrame = true;
	//		mouseClickedLastFrame = true;
	//	} else {
	//		tileUpLastFrame == false;
	//		mouseClickedLastFrame == false;
	//	}
	//}

	////clicking and if set to being moved
	//else if (isBeingMoved) {
	//	auto newPos = sf::Vector2f((sf::Mouse::getPosition(win))) - mouseRelation;
	//	rect.setPosition(newPos);

	//	state = State::UP;

	//	//Last frame:
	//	tileUpLastFrame = true;
	//	mouseClickedLastFrame = true;
	//}

	return state;

}