//
// Created by Magda on 25.03.2022.
//

#include "SimulationModel.h"

#include <thread>
#include <iostream>
#include <time.h>
#include <conio.h>
#include "Shelf.h"
#include "Oven.h"
#include "Cook.h"
#include "Sink.h"
#include "Worktop.h"
#include "ThermalBag.h"
#include "DeliveryMan.h"

const int numberOfCooks = 7;
const int numberOfDeliveryMan = 2;
bool simulationOn = true;

void ovenThread(Oven *oven) {
    oven->live();
}

void getQ() {
    char esc = getch();
    while (esc != 'q') {
        esc = getch();
    }
    simulationOn = false;
}

SimulationModel::SimulationModel() {

}

void SimulationModel::doSimulation() {
    Shelf shelf;
    Oven oven;
    Sink sink;
    Worktop worktop;
    Cook cook;
    DeliveryMan deliveryMan;
    ThermalBag thermalBag;

    std::vector<Cook> cooks;
    std::vector<DeliveryMan> deliveryMen;

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
    std::thread end(getQ);

    while (simulationOn) {
    }

    for (Cook &cook: cooks) {
        cook.stop();
    }

    for (DeliveryMan &deliveryMan: deliveryMen) {
        deliveryMan.stop();
    }

    oven.stop();
    ovenT.join();
    end.join();

}
