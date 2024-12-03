#include "mine.hpp"


int main() {
    Minesweeper game;

    while (game.window.isOpen()) {
        game.handleEvents();
        game.drawGame();
    }

    return 0;
}
