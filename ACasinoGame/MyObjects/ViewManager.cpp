#include "ViewManager.h"
#include <SFML/Graphics.hpp>


ViewManager::ViewManager() {
	sf::RenderWindow window(sf::VideoMode(sf::Vector2u(200, 200)), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
}