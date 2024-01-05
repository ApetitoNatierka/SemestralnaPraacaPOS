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
        std::string prefix = "iteracia";

        if (filename.substr(0, prefix.size()) == prefix) {
            int num = std::stoi(filename.substr(prefix.size()));
            if (num > maxIteration) {
                maxIteration = num;
                maxFile = path + entry.path().filename().string();
                najnovsiaIteracia = num;
            }
        }
    }
}

std::string LatestIteration::getMaxFile() {
    return maxFile;
}

int LatestIteration::spocitajVelkostMatice(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return -1;
    }

    int rows = 0;
    std::string line;
    while (std::getline(file, line)) {
        ++rows;
    }

    return rows - 1;

}

void LatestIteration::setPath(std::string cesta) {
    path = std::move(cesta);
}

std::string LatestIteration::getPath() {
    return path;
}

int LatestIteration::getNajnovsiaIteracia() {
    return najnovsiaIteracia;
}

void LatestIteration::deleteFiles() {
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::filesystem::remove(entry.path());
        }
    }
}



