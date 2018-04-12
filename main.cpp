#include <SFML\Graphics.hpp>
#include <iostream>
#include "Tile.h"


int main() {

	sf::RenderWindow window(sf::VideoMode(512, 512), "Puzzle Game!", sf::Style::Close | sf::Style::Titlebar);
	
	Tile t(1, 2, 3, 512, &window, sf::Color::Red);


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

		t.update();
		t.draw();
		window.display();


	}



	return 0;
}