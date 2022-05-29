//
// Created by Magda on 25.03.2022.
//

#ifndef UNTITLED4_SIMULATIONMODEL_H
#define UNTITLED4_SIMULATIONMODEL_H


#include "Shelf.h"
#include "Oven.h"
#include "Sink.h"
#include "Worktop.h"
#include "DeliveryMan.h"
#include "Cook.h"

class SimulationModel {
private:
    Shelf shelf;
    Oven oven;
    Sink sink;
    Worktop worktop;
    Cook cook;
    DeliveryMan deliveryMan;
    ThermalBag thermalBag;

    const int numberOfCooks = 7;
    const int numberOfDeliveryMan = 2;

    std::vector<Cook> cooks;
    std::vector<DeliveryMan> deliveryMen;

    void displayObjects();

public:
    SimulationModel();

    void doSimulation();
};


#endif