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
    std::vector<std::vector<bool>> matrix;
public:
    explicit GameOfLife() :
    rozsah(0), pocetPrvkovNaGenerovanie(0){};
    int getPocetPrvkov() const{return pocetPrvkovNaGenerovanie;};
    void setPocetPrvkov(int pocet) {pocetPrvkovNaGenerovanie = pocet;};
    void printGame();
    int countNeighbours(int x, int y);
    void update();
    void vygenerujNahodnePrvky();
    void createMatrix(int rozsahMatice);
    void saveState(const std::string &filename);
    void loadState(const std::string &filename);
    void setCoordinatesOnMatrix(int x, int y);
    int getRozsah();
};


#endif //SEMESTRALNA_PRACA_POS_GAMEOFLIFE_H
