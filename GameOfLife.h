//
// Created by keres on 2. 1. 2024.
//

#ifndef SEMESTRALNA_PRACA_POS_GAMEOFLIFE_H
#define SEMESTRALNA_PRACA_POS_GAMEOFLIFE_H
#include <iostream>
#include <vector>
#include "buffer.h"


class GameOfLife {

private:
    buffer * buffer{};
    int rozsah;
    int pocetPrvkovNaGenerovanie;
    std::vector<std::vector<bool>> matrix;
public:
    explicit GameOfLife() :
    rozsah(0), pocetPrvkovNaGenerovanie(0){};
    GameOfLife(GameOfLife& game) {
        this->rozsah = game.rozsah;
        this->pocetPrvkovNaGenerovanie = game.pocetPrvkovNaGenerovanie;
        this->matrix = game.matrix;
        this->buffer = game.buffer;
    }
    void setPocetPrvkov(int pocet) {pocetPrvkovNaGenerovanie = pocet;};
    void printGame();
    int countNeighbours(int x, int y);
    void update();
    void vygenerujNahodnePrvky();
    void createMatrix(int rozsahMatice);
    void saveState(const std::string &filename);
    void loadState(const std::string &filename);
    void setCoordinatesOnMatrix(int x, int y);
    std::string serializeGameState();
    std::vector<std::string> deserializeGameState(const std::string& input);
};


#endif //SEMESTRALNA_PRACA_POS_GAMEOFLIFE_H
