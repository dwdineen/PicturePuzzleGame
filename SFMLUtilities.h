#pragma once

#include <SFML\Graphics.hpp>

namespace sfu {

	//TODO: Write a nicely worded comment or two
	bool mouseClickedOnRectShape(const sf::RectangleShape & rect, const sf::RenderWindow & win);

	//TODO: Write a nicely worded comment or two
	sf::Vector2f mousePosf(const sf::RenderWindow & win);

	//TODO: Write a nicely worded comment or two
	class DragNDrop {
	public:
		enum class State {
			RAISED,
			LOWERED,
			UP,
			DOWN
		};

	private:
		bool isBeingMoved;
		sf::Vector2f mouseRelation;
		State lastState;
	public:
		DragNDrop() : isBeingMoved(false), lastState(State::DOWN) {};

		//This is absolutely terrible style :)
		State update(sf::RectangleShape & rect, const sf::RenderWindow & win);
	};

}
