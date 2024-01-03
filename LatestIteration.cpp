//
// Created by keres on 3. 1. 2024.
//

#include "LatestIteration.h"
#include <filesystem>
#include <string>
#include <iostream>


void LatestIteration::sortNewestSave() {
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        std::string filename = entry.path().filename().string();
        std::string prefix = "iteration";

        if (filename.substr(0, prefix.size()) == prefix) {
            int num = std::stoi(filename.substr(prefix.size()));
            if (num > maxIteration) {
                maxIteration = num;
                maxFile = entry.path();
            }
        }
    }
}

std::string LatestIteration::getMaxFile() {
    return maxFile;
}

int LatestIteration::spocitajVelkostMatice() {
    std::pair<int, int> readMatrixSize(const std::string& maxFile) {
        std::ifstream file(maxFile);
        if (!file) {
            std::cerr << "neda sa otvorit subor:" << maxFile << std::endl;
            return {-1, -1};
        }

        int rows, cols;
        if (!(file >> rows >> cols)) {
            std::cerr << "Nemozne precitat velkost pola zo suboru: " << maxFile << std::endl;
            return {-1, -1};
        }

        return {rows, cols};
    }
}