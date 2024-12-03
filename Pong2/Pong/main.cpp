// This example will use SFML libraries to implement
// the game of Pong

// History: Started from the SFML tutorial code that draws
//          a circle in the window.
// 
//          11/19/24 - Finished declaring class Paddle. Introduced some basic
//                     paddle movements.
//

#include <SFML/Graphics.hpp>

#include "Paddle.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	sf::CircleShape shape(100.f);
	Paddle p1Paddle (sf::Vector2f(30, 100), sf::Vector2f(0,0), sf::Color::Magenta), 
		p2Paddle(sf::Vector2f(window.getSize().x/20, window.getSize().y/5), 
			sf::Vector2f(window.getSize().x-p1Paddle.getSize().x, 0), 
			sf::Color::Magenta);

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
		window.draw(p1Paddle);
		window.draw(p2Paddle);
		window.display();

		//p1Paddle.getGlobalBounds().intersects(shape.getGlobalBounds());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			p1Paddle.move(0, .1);
		}


	}

	return 0;
}