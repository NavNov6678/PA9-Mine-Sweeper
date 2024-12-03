#include "mine.hpp"

Minesweeper::Minesweeper() {
    inGame = false;
    window.create(VideoMode(1200, 700), "Minesweeper");

    if (!startpage.loadFromFile("mine_sweeper.png")) {
        cout << "Error loading start page texture" << endl;
        return;
    }

    start.setTexture(startpage);
    start.setOrigin(Vector2f(startpage.getSize().x / 2.0f, startpage.getSize().y / 2.0f));
    start.setPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
    start.setScale(Vector2f(1, 1));

    circleRadius = 100.0f;
    circleCenter = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    gameRectangle.setSize(Vector2f(400, 200));
    gameRectangle.setFillColor(Color::Green);
    gameRectangle.setPosition(Vector2f((window.getSize().x - 400) / 2, (window.getSize().y - 200) / 2));

    createGrid();
}

void Minesweeper::createGrid() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            RectangleShape square(Vector2f(squareSize, squareSize));
            square.setFillColor(Color::White);
            square.setOutlineThickness(2);
            square.setOutlineColor(Color::Black);
            square.setPosition(i * squareSize, j * squareSize);
            gridSquares.push_back(square);
        }
    }
}



void Minesweeper::handleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            checkMouseClick(mousePos);
        }
    }
}

void Minesweeper::checkMouseClick(Vector2f mousePos) {
    float distance = std::sqrt(std::pow(mousePos.x - circleCenter.x, 2) + std::pow(mousePos.y - circleCenter.y, 2));
    if (distance <= circleRadius) {
        inGame = true;
        cout << "Game Started!" << endl;
    }
}

void Minesweeper::drawGame() {
    window.clear();

    if (!inGame) {
        window.draw(start);
        CircleShape debugCircle(circleRadius);
        debugCircle.setFillColor(Color(255, 255, 255, 100));
        debugCircle.setPosition(circleCenter.x - circleRadius, circleCenter.y - circleRadius);
        window.draw(debugCircle);
    }
    else {
        for (size_t i = 0; i < gridSquares.size(); ++i) {
            RectangleShape& square = gridSquares[i];

            window.draw(square);
        }
    }

    window.display();
}


