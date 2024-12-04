#include "mine.hpp"


int main() {
    RenderWindow window(VideoMode(1200, 700), "Minesweeper");

    Texture startpage;
    if (!startpage.loadFromFile("mine_sweeper.png")) {
        cout << "Error: Could not load mine_sweeper.png" << endl;
        return -1;
    }

    Sprite start;
    start.setTexture(startpage);
    start.setPosition(window.getSize().x / 2 - start.getGlobalBounds().width / 2,
        window.getSize().y / 2 - start.getGlobalBounds().height / 2);

    CircleShape startCircle(180);
    startCircle.setFillColor(Color::Transparent);
    startCircle.setOutlineColor(Color::Green);
    startCircle.setOutlineThickness(3);
    startCircle.setPosition(window.getSize().x / 2 - startCircle.getRadius(),
        window.getSize().y / 2 - startCircle.getRadius());

    bool inStartScreen = true;
    Minesweeper game;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (inStartScreen) {
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f circleCenter = startCircle.getPosition() + Vector2f(startCircle.getRadius(), startCircle.getRadius());
                    float distance = std::sqrt(std::pow(mousePos.x - circleCenter.x, 2) + std::pow(mousePos.y - circleCenter.y, 2));

                    if (distance <= startCircle.getRadius()) {
                        inStartScreen = false;
                    }
                }
            }
        }

        window.clear();

        if (inStartScreen) {
            window.draw(start);
            window.draw(startCircle);
        }
        else {
            game.handleEvents(window);
            game.drawGame(window);
        }

        window.display();
    }

    return 0;
}
