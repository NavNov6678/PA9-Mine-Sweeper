#include "Minesweeper.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
int main() {
    RenderWindow window(VideoMode(1200, 700), "Minesweeper");

    Texture startpage;
    if (!startpage.loadFromFile("mine_sweeper.png")) {
        std::cout << "Error: Could not load mine_sweeper.png" << std::endl;
        return -1;
    }

    Sprite start;
    start.setTexture(startpage);
    start.setPosition(window.getSize().x / 2 - start.getGlobalBounds().width / 2,
        window.getSize().y / 2 - start.getGlobalBounds().height / 2);

    Texture endPage;
    if (!endPage.loadFromFile("end_page.png")) {
        std::cout << "Error: Could not load end_page.png" << std::endl;
        return -1;
    }

    Sprite endSprite;
    endSprite.setTexture(endPage);
    endSprite.setPosition(window.getSize().x / 2 - endSprite.getGlobalBounds().width / 2,
        window.getSize().y / 2 - endSprite.getGlobalBounds().height / 2);

    RectangleShape rectangle(Vector2f(200, 75));
    rectangle.setFillColor(Color::Red);
    rectangle.setPosition(window.getSize().x / 2.0 - rectangle.getSize().x / 2.0,
        window.getSize().y / 2.0 - rectangle.getSize().y / 2.0);

    RectangleShape rectangle2(Vector2f(200, 75));
    rectangle2.setFillColor(Color::Red);
    rectangle2.setPosition(window.getSize().x / 2.0 - rectangle.getSize().x / 2.0,
        window.getSize().y / 2.0 + 100);

    Minesweeper game;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        game.handleEvents(window);
        game.drawGame(window);

        if (game.isGameOver()) {
            window.draw(endSprite);
        }

        window.display();
    }

    return 0;
}
