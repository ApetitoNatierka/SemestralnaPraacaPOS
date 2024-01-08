//
// Created by keres on 2. 1. 2024.
//

#include "GameOfLife.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


void GameOfLife::saveState(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& row : matrix) {
        for (bool cell : row) {
            file << (cell ? '1' : '0');
        }
        file << '\n';
    }
}

void GameOfLife::loadState(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int i = 0;
    int j = 0;
    while (std::getline(file, line)) {
        for (char value : line) {
            matrix.at(i).at(j) = (value == '1');
            ++j;
        }
        ++i;
        j = 0;
    }
}



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
 }

void GameOfLife::createMatrix(int rozsahMatice) {
    this->rozsah = rozsahMatice;
    matrix = std::vector<std::vector<bool>>(rozsah + 1, std::vector<bool>(rozsah +1, false));
}

void GameOfLife::setCoordinatesOnMatrix(int x, int y) {
    matrix.at(x).at(y) = true;

}

std::string GameOfLife::serializeGameState() {
    std::ostringstream oss;

    for (const auto& row : this->matrix) {
        for (bool value : row) {
            oss << (value ? "1" : "0") << ",";
        }
        oss << "\n";
    }

    return oss.str();
}

std::vector<std::string> GameOfLife::deserializeGameState(const std::string& input) {
    std::vector<std::string> result;

    std::string cleanedInput = input;
    cleanedInput.erase(std::remove(cleanedInput.begin(), cleanedInput.end(), ','), cleanedInput.end());

    std::istringstream ss(cleanedInput);
    std::string line;
    while (std::getline(ss, line, ';')) {
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

        size_t pos = line.find(":end");
        if (pos != std::string::npos) {
            line.erase(pos, std::string(":end").length());
        }

        result.push_back(line);
    }

    return result;
}

int GameOfLife::countLines(const std::string& input) {
    int lineCount = 0;
    for (char c : input) {
        if (c == '\n') {
            lineCount++;
        }
    }
    return lineCount;
}

void GameOfLife::loadStateFromString(const std::string& input) {
    std::istringstream ss(input);
    std::string line;
    int i = 0;
    int j = 0;
    while (std::getline(ss, line)) {
        for (char value : line) {
            if (value == '0' || value == '1') {
                matrix.at(i).at(j) = (value == '1');
                ++j;
            }
        }
        ++i;
        j = 0;
    }
}
