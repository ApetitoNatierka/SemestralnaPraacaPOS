//
// Created by keres on 2. 1. 2024.
//

#include "GameOfLife.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

void GameOfLife::printGame() {
    for (int i = 0; i <= this->rozsah; ++i) {
        for (int j = 0; j <= this->rozsah; ++j) {
            if (matrix.at(i).at(j)) {
                std::cout << " 0 ";
            } else {
                std::cout << " . ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "----------------------------------" << std::endl;
}


int GameOfLife::countNeighbours(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            //int noveX = ((x+1)+i+this->rozsah) % this->rozsah;
            //int noveY = ((y+1)+j+this->rozsah) % this->rozsah;
            int noveX = x+i;
            int noveY = y+j;

            if(noveX >= 0 && noveX < rozsah && noveY >= 0 && noveY < rozsah){
                if (matrix.at(noveX).at(noveY)) {
                    ++count;
                }
            }
            
        }
    }
    return count;
}

 void GameOfLife::vygenerujNahodnePrvky() {
    for (int i = 0; i < this->pocetPrvkovNaGenerovanie; ++i) {
        int randomX = rand() % this->rozsah;
        int randomY = rand() % this->rozsah;
        matrix.at(randomX).at(randomY) = true;
    }
}

void GameOfLife::update() {
    std::vector<std::vector<bool>> docasnyMatrix(rozsah + 1, std::vector<bool>(rozsah +1, false));
     for (int i = 0; i < this->rozsah; ++i) {
         for (int j = 0; j < this->rozsah; ++j) {
             int susedia = countNeighbours(i, j);

             if (matrix.at(i).at(j)) {
                 if (susedia < 2) {
                     docasnyMatrix.at(i).at(j) = false;
                 } else if (susedia == 2 || susedia == 3) {
                     docasnyMatrix.at(i).at(j) = true;
                 } else if (susedia > 3) {
                     docasnyMatrix.at(i).at(j) = false;
                 }
             } else {
                 if (susedia == 3) {
                     docasnyMatrix.at(i).at(j) = true;
                 }

             }
         }
     }
     matrix = docasnyMatrix;
 };

