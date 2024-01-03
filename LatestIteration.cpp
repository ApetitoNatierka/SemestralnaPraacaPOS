//
// Created by keres on 3. 1. 2024.
//

#include "LatestIteration.h"
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>


void LatestIteration::sortNewestSave() {
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        std::string filename = entry.path().filename().string();
        std::string prefix = "iteration";

        if (filename.substr(0, prefix.size()) == prefix) {
            int num = std::stoi(filename.substr(prefix.size()));
            if (num > maxIteration) {
                maxIteration = num;
                maxFile = path + entry.path().filename().string();
            }
        }
    }
}

std::string LatestIteration::getMaxFile() {
    return maxFile;
}

int LatestIteration::spocitajVelkostMatice(const std::string& maxFile) {
        std::ifstream file(maxFile);
        if (!file) {
            std::cerr << "Neda sa otvorit subor:" << maxFile << std::endl;
            return 0;
        }

        int rows, cols;
        if (!(file >> rows >> cols)) {
            std::cerr << "Nemozne precitat velkost pola zo suboru: " << maxFile << std::endl;
            return 0;
        }

        return rows;
    }

void LatestIteration::setPath(std::string cesta) {
    path = std::move(cesta);
}

std::string LatestIteration::getPath() {
    return path;
}
