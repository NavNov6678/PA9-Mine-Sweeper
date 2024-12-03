#ifndef MINE_HPP
#define MINE_HPP
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

using namespace sf;
using std::cout;
using std::endl;
using std::vector;

class Minesweeper {
public:
    Minesweeper();

    void startGame();
    void handleEvents();
    void drawGame();
    void createGrid();
    void checkMouseClick(Vector2f mousePos);


    bool inGame;
    RenderWindow window;
    Texture startpage;
    Sprite start;
    RectangleShape gameRectangle;
    const int gridSize = 20;
    const float squareSize = 30.0f;
    vector<RectangleShape> gridSquares;
    float circleRadius;
    Vector2f circleCenter;
};

#endif
