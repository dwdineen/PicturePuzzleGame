#include <SFML\Graphics.hpp>
#include <iostream>
#include "Board.h"
//#include "Tile.h"


int main() {

	sf::RenderWindow window(sf::VideoMode(512, 512), "Puzzle Game!", sf::Style::Close | sf::Style::Titlebar);
	
	Board b(&window, 3, "");


	while (window.isOpen()) {
	
		sf::Event evnt;
		while (window.pollEvent(evnt)) {

			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}

		}
		
		// Clear window
		window.clear(sf::Color::Black);

		b.update();
		b.draw();
		window.display();


	}



	return 0;
}