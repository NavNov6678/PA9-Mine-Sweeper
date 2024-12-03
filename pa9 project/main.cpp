#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>

using namespace sf;
using std::cout;
using std::endl;
using std::vector;

int main() {
    bool inGame = false;
    RenderWindow window(VideoMode(1200, 700), "Minesweeper");

    Texture startpage;
    if (!startpage.loadFromFile("mine_sweeper.png"))
    {
        cout << "Error loading start page texture" << endl;
        return -1;
    }

    Sprite start;
    start.setTexture(startpage);
    start.setOrigin(Vector2f(startpage.getSize().x / 2.0f, startpage.getSize().y / 2.0f));
    start.setPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
    start.setScale(Vector2f(0.65, 0.65));

    float circleRadius = 100.0f;
    Vector2f circleCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);


    const int gridSize = 10;
    const float squareSize = 30.0f;
    vector<RectangleShape> gridSquares;

    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            RectangleShape square(Vector2f(squareSize, squareSize));
            square.setFillColor(Color::White);
            square.setOutlineThickness(2);
            square.setOutlineColor(Color::Black);
            square.setPosition(i * squareSize, j * squareSize);
            gridSquares.push_back(square);
        }
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                float distance = std::sqrt(std::pow(mousePos.x - circleCenter.x, 2) + std::pow(mousePos.y - circleCenter.y, 2));
                if (distance <= circleRadius)
                {
                    inGame = true;
                    cout << "Game Started!" << endl;
                }
            }
        }

        window.clear();

        if (!inGame)
        {
            window.draw(start);
            CircleShape debugCircle(circleRadius);
            debugCircle.setFillColor(Color(255, 255, 255, 100));
            debugCircle.setPosition(circleCenter.x - circleRadius, circleCenter.y - circleRadius);
            window.draw(debugCircle);
        }
        else
        {
            for (size_t i = 0; i < gridSquares.size(); ++i)
            {
                RectangleShape& square = gridSquares[i];
                window.draw(square);
            }
        }

        window.display();
    }

    return 0;
}