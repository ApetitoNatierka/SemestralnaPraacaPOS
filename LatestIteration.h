//
// Created by keres on 3. 1. 2024.
//

#ifndef SEMESTRALNA_PRACA_POS_LATESTITERATION_H
#define SEMESTRALNA_PRACA_POS_LATESTITERATION_H


class LatestIteration {\
private:
    std::string path;
    std::maxIteration = 0;
    std::string maxFile;
public:
    void sortNewestSave();
    void setPath();
    std::string getMaxFile();
    int spocitajVelkostMatice();
};


#endif //SEMESTRALNA_PRACA_POS_LATESTITERATION_H
