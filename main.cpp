#include <SFML\Graphics.hpp>
#include <iostream>


int main() {

	sf::RenderWindow window(sf::VideoMode(512, 512), "Puzzle Game!", sf::Style::Close | sf::Style::Titlebar);
	
	int a = 5;
	int & b = a;
	std::cout << a << " " << b << std::endl;


	while (window.isOpen()) {
	
		sf::Event evnt;
		while (window.pollEvent(evnt)) {

			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}

		}
		
	}



	return 0;
}