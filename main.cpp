#include <SFML\Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "SFMLUtilities.h"
//#include "Tile.h"

//This global will be moved one day
bool keyPressLastFrame = false;

int main() {

	sf::RenderWindow window(sf::VideoMode(900, 900), "Puzzle Game!", sf::Style::Close | sf::Style::Titlebar);
	
	Board b(&window, 3, 900, "");


	while (window.isOpen()) {
	
		sf::Event evnt;
		while (window.pollEvent(evnt)) {

			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}

		}
		
		bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
		bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

		if (Up && !keyPressLastFrame) b.move(sfu::Dir::UP);
		else if (Down && !keyPressLastFrame) b.move(sfu::Dir::DOWN);
		else if (Left && !keyPressLastFrame) b.move(sfu::Dir::LEFT);
		else if (Right && !keyPressLastFrame) b.move(sfu::Dir::RIGHT);

		keyPressLastFrame = Up || Down || Left || Right;

		// Clear window
		window.clear(sf::Color::Black);

		b.update();
		b.draw();
		window.display();


	}



	return 0;
}