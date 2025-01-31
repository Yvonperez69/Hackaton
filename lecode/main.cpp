#include "game.hpp"

int main() {
    const int ROWS = 15;
    const int COLS = 118;

    Game game(ROWS, COLS);
    game.play_game();

    return 0;
}

