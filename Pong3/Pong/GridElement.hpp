#ifndef GRIDELEMENT_HPP
#define GRIDELEMENT_HPP

#include <SFML/Graphics.hpp>

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

#endif
