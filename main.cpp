#include <iostream>
#include "GameOfLife.h"

int main() {
    GameOfLife game(10);
    game.matrix.at(2).at(1) = true;
    game.matrix.at(1).at(0) = true;
    game.matrix.at(1).at(1) = true;
    game.matrix.at(3).at(0) = true;
    game.printGame();
    int i = game.countNeighbours(2, 0);
    std::cout << i;
    return 0;
}
