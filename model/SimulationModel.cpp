//
// Created by Magda on 25.03.2022.
//

#include "SimulationModel.h"

#include <thread>
#include <iostream>
#include <ncurses.h>
#include <time.h>
#include<chrono>
#include "Shelf.h"
#include "Oven.h"
#include "Cook.h"
#include "Sink.h"
#include "Worktop.h"
#include "ThermalBag.h"
#include "DeliveryMan.h"

bool simulationOn = true;

void ovenThread(Oven *oven) {
    oven->live();
}

SimulationModel::SimulationModel() {

}

void displayCook(Cook &cook) {
    static std::array<int, 5> positionsH{5, 20, 35, 45, 60};
    static std::array<int, 8> positionsV{0, 1, 13, 25, 37, 49, 61, 73};
    attron(COLOR_PAIR(1));
    mvprintw(positionsV[cook.getNumberOfCook()], positionsH[char(cook.action)], "      ***       ");
    mvprintw(positionsV[cook.getNumberOfCook()] + 1, positionsH[char(cook.action)], "   *******    ");
    mvprintw(positionsV[cook.getNumberOfCook()] + 2, positionsH[char(cook.action)], "   *********   ");
    mvprintw(positionsV[cook.getNumberOfCook()] + 3, positionsH[char(cook.action)], "/\* ### ### *\\");
    mvprintw(positionsV[cook.getNumberOfCook()] + 4, positionsH[char(cook.action)], "|    @ / @    |");
    mvprintw(positionsV[cook.getNumberOfCook()] + 5, positionsH[char(cook.action)], "\/\      ^    /\/");
    mvprintw(positionsV[cook.getNumberOfCook()] + 6, positionsH[char(cook.action)], "   \   === /    ");
    mvprintw(positionsV[cook.getNumberOfCook()] + 7, positionsH[char(cook.action)], "    \_____/     ");
    mvprintw(positionsV[cook.getNumberOfCook()] + 8, positionsH[char(cook.action)], "     _|_|_     ");
    mvprintw(positionsV[cook.getNumberOfCook()] + 9, positionsH[char(cook.action)], "  *$$$$$$$$$*   ");
    attroff(COLOR_PAIR(1));

    switch (cook.getNumberOfCook()) {
        case 1:
            mvprintw(positionsV[cook.getNumberOfCook()] + 10, positionsH[char(cook.action)], "Maciej");
            break;
        case 2:
            mvprintw(positionsV[cook.getNumberOfCook()] + 10, positionsH[char(cook.action)], "Janek");
            break;
        case 3:
            mvprintw(positionsV[cook.getNumberOfCook()] + 10, positionsH[char(cook.action)], "Albert");
            break;
        case 4:
            mvprintw(positionsV[cook.getNumberOfCook()] + 10, positionsH[char(cook.action)], "Mikolaj");
            break;
        case 5:
            mvprintw(positionsV[cook.getNumberOfCook()] + 10, positionsH[char(cook.action)], "Wojtek");
            break;
        case 6:
            mvprintw(positionsV[cook.getNumberOfCook()] + 10, positionsH[char(cook.action)], "Marek");
            break;
        case 7:
            mvprintw(positionsV[cook.getNumberOfCook()] + 10, positionsH[char(cook.action)], "Kuba");
            break;
    }
}

void displayDeliver(DeliveryMan &deliveryMan) {
    static std::array<int, 3> positionsH{80, 95, 110};
    static std::array<int, 8> positionsV{0, 1, 13};
    attron(COLOR_PAIR(3));
    mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()], positionsH[char(deliveryMan.action)],
             "      ***       ");
    mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()] + 1, positionsH[char(deliveryMan.action)],
             "   *******    ");
    mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()] + 2, positionsH[char(deliveryMan.action)],
             "   *********   ");
    mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()] + 3, positionsH[char(deliveryMan.action)],
             "/\* ### ### *\\");
    mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()] + 4, positionsH[char(deliveryMan.action)],
             "|    @ / @    |");
    mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()] + 5, positionsH[char(deliveryMan.action)],
             "\/\      ^    /\/");
    mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()] + 6, positionsH[char(deliveryMan.action)],
             "   \   === /    ");
    mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()] + 7, positionsH[char(deliveryMan.action)],
             "    \_____/     ");
    mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()] + 8, positionsH[char(deliveryMan.action)],
             "     _|_|_     ");
    mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()] + 9, positionsH[char(deliveryMan.action)],
             "  *$$$$$$$$$*   ");
    attroff(COLOR_PAIR(3));
    switch (deliveryMan.getNumberOfDeliveryMan()) {
        case 1:
            mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()] + 10, positionsH[char(deliveryMan.action)],
                     "Piotr");
            break;
        case 2:
            mvprintw(positionsV[deliveryMan.getNumberOfDeliveryMan()] + 10, positionsH[char(deliveryMan.action)],
                     "Pawel");
            break;
    }

}

void SimulationModel::displayObjects() {
    attron(A_BOLD);
    attron(COLOR_PAIR(2));
    mvprintw(0, 5, "SINK");
    mvprintw(0, 20, "WORKTOP");
    mvprintw(0, 35, "OVEN");
    mvprintw(0, 45, "SHELF");
    mvprintw(0, 60, "WAIT");
    mvprintw(0, 80, "ADD");
    mvprintw(0, 95, "GO");
    mvprintw(0, 110, "WAIT");
    attroff(COLOR_PAIR(2));
    attroff(A_BOLD);
    for (auto &cook: cooks) {
        displayCook(cook);
    }
    for (auto &deliveryMan: deliveryMen) {
        displayDeliver(deliveryMan);
    }

}

void SimulationModel::doSimulation() {

    initscr();
    nodelay(stdscr, TRUE);

    start_color(); //2
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);

    for (int i = 0; i < numberOfCooks; i++) {
        cooks.emplace_back(Cook());
    }

    for (int i = 0; i < numberOfDeliveryMan; i++) {
        deliveryMen.emplace_back(DeliveryMan());
    }

    for (Cook &cook: cooks) {
        cook.start(&sink, &worktop, &oven, &shelf);
    }

    for (DeliveryMan &deliveryMan: deliveryMen) {
        deliveryMan.start(&thermalBag, &shelf);
    }

    std::thread ovenT(ovenThread, &oven);

    while (simulationOn) {
        erase();
        displayObjects();
        refresh();
        std::this_thread::sleep_for(std::chrono::microseconds(200));
    }

    for (Cook &cook: cooks) {
        cook.stop();
    }

    for (DeliveryMan &deliveryMan: deliveryMen) {
        deliveryMan.stop();
    }

    oven.stop();
    ovenT.join();
    endwin();

}
