//
// Created by lordc on 1/5/2024.
//

#ifndef SEMESTRALNA_PRACA_POS_BUFFER_H
#define SEMESTRALNA_PRACA_POS_BUFFER_H

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>

class buffer {
private:
    std::mutex mtx;
    std::vector<std::vector<bool>> matrixF;
};


#endif //SEMESTRALNA_PRACA_POS_BUFFER_H
