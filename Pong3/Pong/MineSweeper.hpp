#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include "GridElement.hpp"
#include <vector>

class Minesweeper {
public:
    Minesweeper();
    void handleEvents(sf::RenderWindow& window);
    void drawGame(sf::RenderWindow& window);
    void generateGrid();
    void revealCell(int x, int y, sf::RenderWindow& window);
    bool isGameOver() const { return gameOver; }
    void resetGame();
    bool checkWin();
    int countMines();
private:
    std::vector<std::vector<GridElement*>> grid;
    bool gameOver;
    void cleanUpGrid();
};

#endif
