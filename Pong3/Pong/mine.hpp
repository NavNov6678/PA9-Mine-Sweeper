#ifndef MINE_HPP
#define MINE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>

using std::cout;
using std::endl;

using namespace sf;

class GridElement {
public:
    virtual void draw(RenderWindow& window, int x, int y) = 0;
    virtual void reveal() = 0;
    virtual bool isRevealed() const = 0;
    virtual ~GridElement() {}
};

class EmptyCell : public GridElement {
public:
    void draw(RenderWindow& window, int x, int y) override;
    void reveal() override;
    bool isRevealed() const override;
private:
    bool revealed = false;
};

class MineCell : public GridElement {
public:
    void draw(RenderWindow& window, int x, int y) override;
    void reveal() override;
    bool isRevealed() const override;
private:
    bool revealed = false;
};

class NumberCell : public GridElement {
public:
    NumberCell(int number);
    void draw(RenderWindow& window, int x, int y) override;
    void reveal() override;
    bool isRevealed() const override;
private:
    int number;
    bool revealed = false;
};

class Minesweeper {
public:
    Minesweeper();
    void handleEvents(RenderWindow& window);
    void drawGame(RenderWindow& window);
    void generateGrid();
    void revealCell(int x, int y, RenderWindow& window);
    bool isGameOver() const;
    void resetGame();
    bool checkWin();
    int countMines();
private:
    std::vector<std::vector<GridElement*>> grid;
    bool gameOver;
    void cleanUpGrid();
};

#endif
