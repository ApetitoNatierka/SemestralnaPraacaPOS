#include <iostream>
#include "GameOfLife.h"
#include <chrono>
#include <thread>
#include <cstdlib>



int main() {
    std::cout<< "Napis rozsah hracej plochy: "<< std::endl;
    int rozsahHry;
    std::cin >> rozsahHry;
    GameOfLife game(rozsahHry);
    int choice;
    std::cout << "Vyber ci chces vygenerovat nahodne prvky(1) alebo si zvolit vlastne(2): "<< std::endl;
    std::cin >> choice;
    bool opakovanie = true;
    while(opakovanie == true) {
        switch (choice) {
            case 1: std::cout << "Kolko prvkov chces vygenerovat?"<< std::endl;
                int pocetPrvkov;
                std::cin >> pocetPrvkov;
                game.setPocetPrvkov(pocetPrvkov);
                opakovanie = false;
                break;
            case 2: std::cout << "Kolko prvkov chces vygenerovat?" << std::endl;
                int pocetNaVytvorenie;
                for (int i = 0; i < pocetNaVytvorenie; ++i) {
                    std::cout << "Napis x a y suradnice vlastneho prvku:?"<< std::endl;
                    int x;
                    std::cin >> x;
                    int y;
                    std::cin >> y;
                    game.matrix.at(x).at(y) = true;
                    opakovanie = false;
                }
                break;
            default: std::cout << "Musis stlacit 1 alebo 2" << std::endl;
    }


    }
    game.vygenerujNahodnePrvky();
    game.matrix.at(1).at(0) = true;
    game.matrix.at(2).at(1) = true;
    game.matrix.at(2).at(2) = true;
    game.matrix.at(1).at(2) = true;
    game.matrix.at(0).at(2) = true;

    game.printGame();

    int i=0;
    while(i<1000){
        game.update();
        game.printGame();
        i++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
