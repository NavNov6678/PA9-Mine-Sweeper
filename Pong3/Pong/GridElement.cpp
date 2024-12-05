#include "GridElement.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using std::cout;
using std::endl;

void EmptyCell::draw(RenderWindow& window, int x, int y) {
    RectangleShape cell(Vector2f(60, 60));
    cell.setPosition(x * 60, y * 60);
    if (isRevealed()) {
        cell.setFillColor(Color::White);
    }
    else {
        cell.setFillColor(Color::Cyan);
    }
    cell.setOutlineColor(Color::Black);
    cell.setOutlineThickness(1);
    window.draw(cell);
}

void EmptyCell::reveal() {
    revealed = true;
}

bool EmptyCell::isRevealed() const {
    return revealed;
}

void MineCell::draw(RenderWindow& window, int x, int y) {
    RectangleShape cell(Vector2f(60, 60));
    cell.setPosition(x * 60, y * 60);
    if (isRevealed()) {
        cell.setFillColor(Color::Black);
    }
    else {
        cell.setFillColor(Color::Red);
    }
    cell.setOutlineColor(Color::Black);
    cell.setOutlineThickness(1);
    window.draw(cell);
}

void MineCell::reveal() {
    revealed = true;
}

bool MineCell::isRevealed() const {
    return revealed;
}

NumberCell::NumberCell(int number) : number(number) {}

void NumberCell::draw(RenderWindow& window, int x, int y) {
    RectangleShape cell(Vector2f(60, 60));
    cell.setPosition(x * 60, y * 60);
    if (isRevealed()) {
        cell.setFillColor(Color::White);
    }
    else {
        cell.setFillColor(Color::Cyan);
    }
    cell.setOutlineColor(Color::Black);
    cell.setOutlineThickness(1);
    window.draw(cell);

    if (isRevealed()) {
        Text numberText;
        numberText.setString(std::to_string(number));
        numberText.setCharacterSize(24);
        numberText.setFillColor(Color::Black);
        numberText.setPosition(x * 60 + 20, y * 60 + 20);
        window.draw(numberText);
    }
}

void NumberCell::reveal() {
    revealed = true;
}

bool NumberCell::isRevealed() const {
    return revealed;
}
