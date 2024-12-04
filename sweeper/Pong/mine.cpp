#include "mine.hpp"

Minesweeper::Minesweeper() {
    generateGrid();
}

void EmptyCell::draw(RenderWindow& window, int x, int y) {
    RectangleShape cell(Vector2f(60, 60));
    cell.setPosition(x * 60, y * 60);
    cell.setFillColor(Color::White);
    cell.setOutlineColor(Color::Black);
    cell.setOutlineThickness(1);
    window.draw(cell);
}

void MineCell::draw(RenderWindow& window, int x, int y) {
    RectangleShape cell(Vector2f(60, 60));
    cell.setPosition(x * 60, y * 60);
    cell.setFillColor(Color::Red);
    window.draw(cell);
}

NumberCell::NumberCell(int number) : number(number) {}

void NumberCell::draw(RenderWindow& window, int x, int y) {
    RectangleShape cell(Vector2f(60, 60));
    cell.setPosition(x * 60, y * 60);
    cell.setFillColor(Color::White);
    cell.setOutlineColor(Color::Black);
    cell.setOutlineThickness(1);
    window.draw(cell);

    Text numberText;
    Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        cout << "Error loading font" << endl;
    }
    numberText.setFont(font);
    numberText.setString(std::to_string(number));
    numberText.setCharacterSize(30);
    numberText.setFillColor(Color::Black);
    numberText.setPosition(x * 60 + 20, y * 60 + 10);
    window.draw(numberText);
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

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            if (dynamic_cast<MineCell*>(grid[x][y])) {
                continue;
            }
            int mineCount = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && ny >= 0 && nx < 10 && ny < 10 &&
                        dynamic_cast<MineCell*>(grid[nx][ny])) {
                        ++mineCount;
                    }
                }
            }
            grid[x][y] = new NumberCell(mineCount);
        }
    }
}

void Minesweeper::handleEvents(RenderWindow& window) {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2i mousePos = Mouse::getPosition(window);
        int x = mousePos.x / 60;
        int y = mousePos.y / 60;

        if (x >= 0 && y >= 0 && x < 10 && y < 10) {
            revealCell(x, y);
        }
    }
}

void Minesweeper::drawGame(RenderWindow& window) {
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            grid[x][y]->draw(window, x, y);
        }
    }
}

void Minesweeper::revealCell(int x, int y) {
    if (dynamic_cast<MineCell*>(grid[x][y])) {
        cout << "Mine hit at (" << x << ", " << y << ")!" << endl;
    }
}

void Minesweeper::cleanUpGrid() {
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            delete grid[x][y];
        }
    }
}
