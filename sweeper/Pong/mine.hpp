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
    virtual void draw(sf::RenderWindow& window, int x, int y) = 0;
    virtual ~GridElement() {}
};

class EmptyCell : public GridElement {
public:
    void draw(sf::RenderWindow& window, int x, int y) override;
};

class MineCell : public GridElement {
public:
    void draw(sf::RenderWindow& window, int x, int y) override;
};

class NumberCell : public GridElement {
public:
    NumberCell(int number);
    void draw(sf::RenderWindow& window, int x, int y) override;
private:
    int number;
};

class Minesweeper {
public:
    Minesweeper();
    void handleEvents(sf::RenderWindow& window);
    void drawGame(sf::RenderWindow& window);
    void generateGrid();
    void revealCell(int x, int y);

private:
    std::vector<std::vector<GridElement*>> grid;
    void cleanUpGrid();
};

#endif // MINE_HPP
