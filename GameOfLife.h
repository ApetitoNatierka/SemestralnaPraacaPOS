//
// Created by keres on 2. 1. 2024.
//

#ifndef SEMESTRALNA_PRACA_POS_GAMEOFLIFE_H
#define SEMESTRALNA_PRACA_POS_GAMEOFLIFE_H
#include <iostream>
#include <vector>


class GameOfLife {

private:
    int rozsah;
    int pocetPrvkovNaGenerovanie;
public:
    explicit GameOfLife(int paRozsah) :
    rozsah(paRozsah), pocetPrvkovNaGenerovanie(10), matrix(paRozsah + 1, std::vector<bool>(paRozsah +1, false)){};
    void printGame();
    int countNeighbours(int x, int y);
    void update();
    void vygenerujNahodnePrvky();
    std::vector<std::vector<bool>> matrix;

};


#endif //SEMESTRALNA_PRACA_POS_GAMEOFLIFE_H
