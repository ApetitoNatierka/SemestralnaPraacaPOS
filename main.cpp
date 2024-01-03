#include <iostream>
#include "GameOfLife.h"
#include "LatestIteration.h"
#include <chrono>
#include <thread>
#include <filesystem>
#include <string>
#include <iostream>



int main() {
    LatestIteration load;
    load.sortNewestSave();
    std::cout<<"Chces nacitat hru(1) alebo vytvorit novu(2)?"<<std::endl;
    std::cin>> zaciatok;
    int zaciatok;
    bool opakovanie1 = true;
    while(opakovanie1) {
        switch (zaciatok) {
            case 1 : GameOfLife game(load.spocitajVelkostMatice());
                    game.loadState(load.getMaxFile());
                    opakovanie1 = false;
                    break;
            case 2: std::cout<< "Napis rozsah hracej plochy: "<< std::endl;
                    int rozsahHry;
                    std::cin >> rozsahHry;
                    GameOfLife game(rozsahHry);
                    int choice;
                     std::cout << "Vyber ci chces vygenerovat nahodne prvky(1) alebo si zvolit vlastne(2): "<< std::endl;
                    std::cin >> choice;
                    bool opakovanie2 = true;
                    while(opakovanie2) {
                    switch (choice) {
                        case 1: std::cout << "Kolko prvkov chces vygenerovat?"<< std::endl;
                            int pocetPrvkov;
                            std::cin >> pocetPrvkov;
                            game.setPocetPrvkov(pocetPrvkov);
                            opakovanie2 = false;
                            break;
                        case 2: std::cout << "Kolko prvkov chces vygenerovat?" << std::endl;
                            int pocetNaVytvorenie;
                            std::cin >> pocetNaVytvorenie;
                            for (int i = 0; i < pocetNaVytvorenie; ++i) {
                                std::cout << "Napis x a y suradnice vlastneho prvku:?"<< std::endl;
                                int x;
                                std::cin >> x;
                                int y;
                                std::cin >> y;
                                game.matrix.at(x).at(y) = true;
                                opakovanie2 = false;
                            }
                            break;
                        default: std::cout << "Musis stlacit 1 alebo 2" << std::endl;
                    }


                }
                    break;
            default: std::cout << "Musis stlacit 1 alebo 2" << std::endl;
        }
    }
    game.printGame();

    int cisloIteracie = 0;
    std::string menoSuboru = "iteracia";
    while(true){
        game.update();
        game.printGame();
        ++cisloIteracie;
        game.saveState(menoSuboru += std::to_string(cisloIteracie));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
