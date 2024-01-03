#include <iostream>
#include "GameOfLife.h"
#include <chrono>
#include <thread>

int main() {
    GameOfLife game(10);
    game.matrix.at(1).at(0) = true;
    game.matrix.at(2).at(1) = true;
    game.matrix.at(2).at(2) = true;
    game.matrix.at(1).at(2) = true;
    game.matrix.at(0).at(2) = true;

    game.printGame();

    int i=0;
    while(i<1000){
        game.update();
        game.printGame();
        i++;
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

    return 0;
}
