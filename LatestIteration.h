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
    int najnovsiaIteracia;
public:
    void sortNewestSave();
    void setPath(std::string cesta);
    std::string getPath();
    std::string getMaxFile();
    int spocitajVelkostMatice(const std::string& filename);
    int getNajnovsiaIteracia();
    void deleteFiles();
};


#endif //SEMESTRALNA_PRACA_POS_LATESTITERATION_H
