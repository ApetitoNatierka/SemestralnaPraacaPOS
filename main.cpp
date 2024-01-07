#include <iostream>
#include "GameOfLife.h"
#include "LatestIteration.h"
#include <chrono>
#include <thread>
#include <string>
#include <filesystem>
#include <mutex>
#include <atomic>
#include "my_socket.h"
#include <Windows.h>


std::mutex gameMutex;
std::atomic<bool> gameRunning(true);
bool pauseGame = false;
bool reverseMode = false;


void gameThread(GameOfLife &game, LatestIteration& load, int& cisloIteracie, const std::string& menoSuboru) {
    while (gameRunning) {
        std::unique_lock<std::mutex> lock(gameMutex);

        if (!pauseGame) {
            if (reverseMode) {
                load.sortNewestSave();
                std::string cesta = "iteracia" + std::to_string(load.getNajnovsiaIteracia());
                game.loadState(load.getPath() + cesta);
                game.printGame();
                std::filesystem::remove(load.getPath() + cesta);
                cisloIteracie--;

                if (cesta == "iteracia1") {
                    std::cout << "Prisli ste na zaciatok simulacie. Stlacte sipku vpravo pre pokracovanie a Esc pre ukoncenie." << std::endl;

                    while (true) {
                        if (GetAsyncKeyState(VK_SPACE) & 0x8001) {
                            break;
                        }
                        if (GetAsyncKeyState(VK_RIGHT) & 0x8001) {
                            std::cout << "Pokracujete v doprednom chode simulacie." << std::endl;
                            break;
                        }
                        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                            gameRunning = false;
                            break;
                        }

                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                }

            } else {
                ++cisloIteracie;
                game.update();
                game.saveState(load.getPath() + menoSuboru += std::to_string(cisloIteracie));
                game.printGame();
            }
        }

        lock.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void inputThread(GameOfLife& game, LatestIteration& load) {
    while (gameRunning) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            gameRunning = false;
        }

        if (GetAsyncKeyState(VK_SPACE) & 0x8001) {
            pauseGame = !pauseGame;
            if (!pauseGame) {
                reverseMode = false;
            }
            std::cout << (pauseGame ? "Game Paused" : "Game Resumed") << std::endl;
        }

        if (GetAsyncKeyState(VK_LEFT) & 0x8001) {
            reverseMode = true;
            std::cout << "Reverse Mode Activated" << std::endl;
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8001) {
            reverseMode = false;
            std::cout << "Update Mode Activated" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


int main() {

    GameOfLife game;
    LatestIteration load;
    load.setPath("C:/saves/");
    load.sortNewestSave();
    std::cout<<"Chces nacitat hru(1) ,alebo vytvorit novu(2) alebo nacitat so servera(3)?"<<std::endl;
    int zaciatok;
    bool opakovanie1 = true;
    bool opakovanie2 = true;
    int choice;
    int rozsahHry;
    int bytesRead;
    std::string messageToServer;
    MySocket* socket = nullptr;
    std::cin>> zaciatok;
    opakovanie1 = true;
    while(opakovanie1) {
        switch (zaciatok) {
            case 1 : game.createMatrix(load.spocitajVelkostMatice(load.getMaxFile()));
                    game.loadState(load.getMaxFile());
                    opakovanie1 = false;
                    break;
            case 2 : load.deleteFiles();
                    std::cout<< "Napis rozsah hracej plochy: "<< std::endl;
                    std::cin >> rozsahHry;
                    game.createMatrix(rozsahHry);
                     std::cout << "Vyber ci chces vygenerovat nahodne prvky(1) alebo si zvolit vlastne(2): "<< std::endl;
                    std::cin >> choice;
                    while(opakovanie2) {
                        switch (choice) {
                            case 1: std::cout << "Kolko prvkov chces vygenerovat?"<< std::endl;
                                int pocetPrvkov;
                                std::cin >> pocetPrvkov;
                                game.setPocetPrvkov(pocetPrvkov);
                                game.vygenerujNahodnePrvky();
                                opakovanie2 = false;
                                opakovanie1 = false;
                                break;
                            case 2: std::cout << "Kolko prvkov chces vygenerovat?" << std::endl;
                                int pocetNaVytvorenie;
                                std::cin >> pocetNaVytvorenie;
                                for (int i = 0; i < pocetNaVytvorenie; ++i) {
                                    std::cout << "Napis x a y suradnice vlastneho prvku: (Napis x + enter a potom y + enter)?"<< std::endl;
                                    int x;
                                    std::cin >> x;
                                    int y;
                                    std::cin >> y;
                                    game.setCoordinatesOnMatrix(x,y);
                                    opakovanie2 = false;
                                    opakovanie1 = false;
                                }
                                break;
                            default: std::cout << "Musis stlacit 1 alebo 2" << std::endl;
                        }
                    }
                    break;
            case 3 :
                std::cout << "Implementing" << std::endl;
                opakovanie1 = true;
                break;
            default:
                std::cout << "Musite vybrat 1, 2 alebo 3" << std::endl;
        }

    }

    int cisloIteracie;
    if (!std::filesystem::is_empty(load.getPath()) > 0) {
        cisloIteracie = load.getNajnovsiaIteracia();
    } else cisloIteracie = 0;
    std::string menoSuboru = "iteracia";

    if (cisloIteracie == 0){
        ++cisloIteracie;
        game.saveState(load.getPath() + menoSuboru += std::to_string(cisloIteracie));
    }
    game.printGame();

    std::thread gameUpateThread(gameThread, std::ref(game), std::ref(load), std::ref(cisloIteracie), std::cref(menoSuboru));
    std::thread inputReadThread(inputThread, std::ref(game), std::ref(load));

    gameUpateThread.join();
    inputReadThread.join();

    std::cout << "Finalna Game of Life: " << std::endl;
    game.printGame();

    int ulozit;
    std::cout << "Zelate si vzor ulozit na server ? ANO(1)/NIE(2) " << std::endl;
    std::cin>> ulozit;

    switch (ulozit) {

        case 1 :
            socket = MySocket::createConnection("frios2.fri.uniza.sk", 13579);

            messageToServer += game.serializeGameState() + ";";

            if(socket != nullptr) {
                socket->sendData(messageToServer);
            }

            std::this_thread::sleep_for(std::chrono::seconds(3));

            std::cout << "Hra bola ulozena na server. Dovidenia" << std::endl;
            break;

        case 2:
            std::cout << "Dovidenia" << std::endl;
            break;

        default:
            std::cout << "Musis vybrat 1 alebo 2" << std::endl;
            break;
    }

    return 0;
}
