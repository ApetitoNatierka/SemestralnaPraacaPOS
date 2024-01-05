cmake_minimum_required(VERSION 3.18)
project(semestralna_praca_pos)

set(CMAKE_CXX_STANDARD 17)

add_executable(semestralna_praca_pos main.cpp
        GameOfLife.cpp
        GameOfLife.h
        LatestIteration.cpp
        LatestIteration.h
        buffer.cpp
        buffer.h)
