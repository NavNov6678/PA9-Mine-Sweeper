#include "mine.hpp"

Minesweeper::Minesweeper() : gameOver(false) {
    generateGrid();
}

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
        cell.setFillColor(Color::Red);
    }
    else {
        cell.setFillColor(Color::Cyan);
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
}

void NumberCell::reveal() {
    revealed = true;
}

bool NumberCell::isRevealed() const {
    return revealed;
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
            revealCell(x, y, window);
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

void Minesweeper::revealCell(int x, int y, RenderWindow& window) {
    if (dynamic_cast<MineCell*>(grid[x][y])) {
        cout << "Mine hit at (" << x << ", " << y << ")!" << endl;
        gameOver = true;
    }
    grid[x][y]->reveal();
}

void Minesweeper::cleanUpGrid() {
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            delete grid[x][y];
        }
    }
}

void Minesweeper::resetGame() {
    cleanUpGrid();
    generateGrid();
    gameOver = false;
}

bool Minesweeper::checkWin() {
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            if ((dynamic_cast<EmptyCell*>(grid[x][y]) || dynamic_cast<NumberCell*>(grid[x][y])) && !grid[x][y]->isRevealed()) {
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
