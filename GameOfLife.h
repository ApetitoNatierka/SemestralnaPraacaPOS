//
// Created by keres on 2. 1. 2024.
//

#ifndef SEMESTRALNA_PRACA_POS_GAMEOFLIFE_H
#define SEMESTRALNA_PRACA_POS_GAMEOFLIFE_H


class GameOfLife {

private:
    int rozsah;

public:
    GameOfLife(int paRozsah) :
    rozsah(paRozsah) {};
    void printGame();
    int countNeighbours();
    void update();
};


#endif //SEMESTRALNA_PRACA_POS_GAMEOFLIFE_H
