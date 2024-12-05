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

    Texture endPage;
    if (!endPage.loadFromFile("end_page.png")) {
        cout << "Error: Could not load end_page.png" << endl;
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
    rectangle2.setPosition(window.getSize().x / 2.0 - rectangle2.getSize().x / 2.0,
        window.getSize().y / 4.0 - rectangle2.getSize().y / 4.0);

    RectangleShape rectangle3(Vector2f(200, 75));
    rectangle3.setFillColor(Color::Red);
    rectangle3.setPosition(window.getSize().x / 2.0 - rectangle3.getSize().x / 2.0,
        window.getSize().y / 1.5 - rectangle3.getSize().y / 1.5);

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error: Could not load arial.ttf" << endl;
        return -1;
    }

    Text replayText;
    replayText.setFont(font);
    replayText.setString("Replay");
    replayText.setCharacterSize(20);
    replayText.setFillColor(Color::White);
    replayText.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2 - replayText.getGlobalBounds().width / 2,
        rectangle.getPosition().y + rectangle.getSize().y / 2 - replayText.getGlobalBounds().height / 2);

    Text lostText;
    lostText.setFont(font);
    lostText.setString("you lose");
    lostText.setCharacterSize(30);
    lostText.setFillColor(Color::White);
    lostText.setPosition(rectangle2.getPosition().x + rectangle2.getSize().x / 2 - lostText.getGlobalBounds().width / 2,
        rectangle2.getPosition().y + rectangle2.getSize().y / 4 - lostText.getGlobalBounds().height / 4);

    Text exitText;
    exitText.setFont(font);
    exitText.setString("exit");
    exitText.setCharacterSize(30);
    exitText.setFillColor(Color::White);
    exitText.setPosition(rectangle3.getPosition().x + rectangle3.getSize().x / 2 - exitText.getGlobalBounds().width / 2,
        rectangle3.getPosition().y + rectangle3.getSize().y / 4 - exitText.getGlobalBounds().height / 4);

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

            if (event.type == Event::MouseButtonPressed && !inStartScreen && game.isGameOver()) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (rectangle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        game.resetGame();
                        inStartScreen = true;
                    }
                    else if (exitText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();  
                    }
                }
            }
        }

        window.clear();

        if (inStartScreen) {
            window.draw(start);
            window.draw(startCircle);
        }
        else if (game.isGameOver()) {
            window.draw(endSprite);
            window.draw(rectangle);
            window.draw(rectangle2);
            window.draw(replayText);
            window.draw(lostText);
            window.draw(rectangle3);
            window.draw(exitText);
        }
        else {
            game.handleEvents(window);
            game.drawGame(window);
        }

        window.display();
    }

    return 0;
}
