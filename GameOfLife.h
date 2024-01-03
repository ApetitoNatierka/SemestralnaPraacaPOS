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
    rozsah(0), pocetPrvkovNaGenerovanie(0), matrix(paRozsah + 1, std::vector<bool>(paRozsah +1, false)){};
    int getPocetPrvkov() const{return pocetPrvkovNaGenerovanie;};
    void setPocetPrvkov(int pocet) {pocetPrvkovNaGenerovanie = pocet;};
    void printGame();
    int countNeighbours(int x, int y);
    void update();
    void vygenerujNahodnePrvky();
    std::vector<std::vector<bool>> matrix;

    void saveState(const std::string &filename);

    void loadState(const std::string &filename);
};


#endif //SEMESTRALNA_PRACA_POS_GAMEOFLIFE_H
