//
// Created by keres on 3. 1. 2024.
//

#ifndef SEMESTRALNA_PRACA_POS_LATESTITERATION_H
#define SEMESTRALNA_PRACA_POS_LATESTITERATION_H
#include <iostream>
#include <filesystem>

class LatestIteration {\
private:
    std::string path;
    int maxIteration = 0;
    std::string maxFile;
public:
    void sortNewestSave();
    void setPath(std::string cesta);
    std::string getPath();
    std::string getMaxFile();
    static int spocitajVelkostMatice(const std::string& maxFile);
};


#endif //SEMESTRALNA_PRACA_POS_LATESTITERATION_H
