#pragma once

#include <cmath>
#include <SFML\Graphics.hpp>

namespace sfu {

	enum Dir {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	//Return unit vector;
	sf::Vector2f vUnit(Dir dir);

	sfu::Dir getDirAtoB(const sf::Vector2f & A, const sf::Vector2f & B);

	//TODO: Write a nicely worded comment or two
	bool mouseClickedOnRectShape(const sf::RectangleShape & rect, const sf::RenderWindow & win);

	//TODO: Write a nicely worded comment or two
	sf::Vector2f mousePosf(const sf::RenderWindow & win);
	
	sf::Vector2f boundRect(const sf::RectangleShape & rect, const sf::FloatRect & bound);

	sf::FloatRect concatRects(const sf::RectangleShape & rect1, const sf::RectangleShape & rect2);
	sf::FloatRect concatRects(const sf::FloatRect & rect1, const sf::FloatRect & rect2);

	bool rectsClose(const sf::RectangleShape & a, const sf::RectangleShape & b, float delta);
	bool pointsClose(const sf::Vector2f & a, const sf::Vector2f & b, float delta);

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
		bool mouseClickedLastFrame = false;
		bool tileUpLastFrame = false;
		sf::Vector2f mouseRelation;
	public:
		DragNDrop() {};

		State update(sf::RectangleShape & rect, const sf::RenderWindow & win);
	};


}
