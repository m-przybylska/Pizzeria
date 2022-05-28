//
// Created by Magda on 25.03.2022.
//

#include "SimulationModel.h"

#include <thread>
#include <iostream>
#include <ncurses.h>
#include <time.h>
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

void displayObjects(){
    attron(A_BOLD);
    mvprintw(0, 5, "SINK");
    mvprintw(0, 20, "WORKTOP");
    mvprintw(0, 35, "OVEN");
    mvprintw(0, 45, "SHELF");
    mvprintw(0, 60, "THERMAL BAG");
}

void displayCook(int x_position, int cookIndeks){
    switch(cookIndeks){
        case 1:
            mvprintw(15, x_position, "Maciek");
            break;
        case 2:
            mvprintw(25, x_position, "Janek");
            break;
        case 3:
            mvprintw(35, x_position, "Piotrek");
            break;
        case 4:
            mvprintw(45, x_position, "Mikolaj");
            break;
        case 5:
            mvprintw(55, x_position, "Wojtek");
            break;
        case 6:
            mvprintw(65, x_position, "Marek");
            break;
        case 7:
            mvprintw(75, x_position, "Kuba");
            break;
    }
}

void displayDeliver(int x_position, int deliverIndeks){
    switch(cookIndeks){
        case 1:
            mvprintw(15, x_position, "Antek");
            break;
        case 2:
            mvprintw(25, x_position, "Tadek");
            break;
    }
}

void SimulationModel::doSimulation() {

    initscr();
    nodelay(stdscr, TRUE);

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
        refresh();
        displayObjects();
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