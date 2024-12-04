// This example will use SFML libraries to implement
// the game of Pong

// History: Started from the SFML tutorial code that draws
//          a circle in the window.
// 
//          11/20/24 - Implemented some collision detection and audio.
// 
//          11/19/24 - Finished declaring class Paddle. Introduced some basic
//                     paddle movements.
//editing

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

#include "Paddle.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	
	Paddle p1Paddle (sf::Vector2f(30, 100), sf::Vector2f(0,0), sf::Color::Magenta), 
		p2Paddle(sf::Vector2f(window.getSize().x/20, window.getSize().y/5), 
			sf::Vector2f(window.getSize().x-p1Paddle.getSize().x, 0), 
			sf::Color::Magenta);
	sf::CircleShape shape(window.getSize().x/20);

	shape.setFillColor(sf::Color::Green);
	shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	int direction = 1;

	sf::Music mus;

	mus.openFromFile("orchestral.ogg");
	mus.play();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		shape.move(direction * .01, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			p1Paddle.move(0, .1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			p2Paddle.move(0, .1);
		}

		if (p1Paddle.getGlobalBounds().intersects(shape.getGlobalBounds()))
		{
			direction *= -1;
		}
		if (p2Paddle.getGlobalBounds().intersects(shape.getGlobalBounds()))
		{
			direction *= -1;
		}

		window.clear();
		window.draw(shape);
		window.draw(p1Paddle);
		window.draw(p2Paddle);
		window.display();
		


	}

	return 0;
}