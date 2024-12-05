#include "Minesweeper.hpp"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace sf;

Minesweeper::Minesweeper() : gameOver(false) {
    generateGrid();
}

void Minesweeper::generateGrid() {
    grid.resize(10, std::vector<GridElement*>(10, nullptr));

    srand(time(0));

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            int randNum = rand() % 10;
            if (randNum == 0) {
                grid[x][y] = new MineCell();
            }
            else {
                grid[x][y] = new EmptyCell();
            }
        }
    }

    // Fill numbers around mines...
}

void Minesweeper::handleEvents(RenderWindow& window) {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2i mousePos = Mouse::getPosition(window);
        int x = mousePos.x / 60;
        int y = mousePos.y / 60;

        if (x >= 0 && y >= 0 && x < 10 && y < 10) {
            revealCell(x, y, window);
        }
    }
}

void Minesweeper::revealCell(int x, int y, RenderWindow& window) {
    if (dynamic_cast<MineCell*>(grid[x][y])) {
       std:: cout << "Mine hit at (" << x << ", " << y << ")!" <<std:: endl;
        gameOver = true;
    }
    grid[x][y]->reveal();
}

void Minesweeper::drawGame(RenderWindow& window) {
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            grid[x][y]->draw(window, x, y);
        }
    }
}

void Minesweeper::resetGame() {
    cleanUpGrid();
    gameOver = false;
    generateGrid();
}

void Minesweeper::cleanUpGrid() {
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            delete grid[x][y];
        }
    }
    grid.clear();
}

bool Minesweeper::checkWin() {
    // Check if all cells are revealed (except mines).
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            if (!grid[x][y]->isRevealed()) {
                return false;
            }
        }
    }
    return true;
}

int Minesweeper::countMines() {
    int mineCount = 0;
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            if (dynamic_cast<MineCell*>(grid[x][y])) {
                ++mineCount;
            }
        }
    }
    return mineCount;
}
