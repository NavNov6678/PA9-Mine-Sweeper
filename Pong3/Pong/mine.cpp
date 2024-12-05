#include "mine.hpp"

Minesweeper::Minesweeper() : gameOver(false) {
    generateGrid();  // Initial grid setup
}

void Minesweeper::handleEvents(RenderWindow& window) {
    // Handle mouse clicks or other events for the game
    if (gameOver) return;  // Do nothing if the game is over
    // You can add logic for handling grid clicks or game-related events
}

void Minesweeper::drawGame(RenderWindow& window) {
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            // If the game is over, reveal all mines
            if (gameOver) {
                if (dynamic_cast<MineCell*>(grid[x][y]) && !grid[x][y]->isRevealed()) {
                    grid[x][y]->reveal();  // Reveal all mines when the game is over
                }
            }
            grid[x][y]->draw(window, x, y);  // Draw the cell (either empty, mine, or number)
        }
    }
}

void Minesweeper::generateGrid() {
    // Set up the grid and place mines and numbers on the grid
    grid.resize(10, std::vector<GridElement*>(10, nullptr));

    // Fill the grid with EmptyCell objects initially
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            grid[x][y] = new EmptyCell();  // This should be a method for creating EmptyCell objects
        }
    }

    // Place some mines and numbers on the grid
    int mineCount = 15;  // Adjust as needed
    while (mineCount > 0) {
        int x = rand() % 10;
        int y = rand() % 10;

        if (dynamic_cast<EmptyCell*>(grid[x][y])) {
            delete grid[x][y];
            grid[x][y] = new MineCell();
            --mineCount;
        }
    }

    // After placing mines, you would generate number cells for the surrounding areas
}

void Minesweeper::revealCell(int x, int y, RenderWindow& window) {
    if (gameOver || grid[x][y]->isRevealed()) return;
    grid[x][y]->reveal();  // Reveal the selected cell
    // Handle revealing the cell here (empty, mine, or number)
}

bool Minesweeper::isGameOver() const {
    return gameOver;
}

void Minesweeper::resetGame() {
    // Clean up old grid and reset the game
    cleanUpGrid();
    gameOver = false;
    generateGrid();
}

bool Minesweeper::checkWin() {
    // Implement win condition logic (e.g., checking if all non-mine cells are revealed)
    return false;
}

void Minesweeper::cleanUpGrid() {
    // Clean up dynamically allocated grid elements
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            delete grid[x][y];
        }
    }
    grid.clear();
}

int Minesweeper::countMines() {
    // Count the number of mines on the grid (can be used for checking win conditions)
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
