//
// Created by Magda on 25.03.2022.
//

#ifndef UNTITLED4_SIMULATIONMODEL_H
#define UNTITLED4_SIMULATIONMODEL_H


#include "Oven.h"

class SimulationModel {

private:
    int numberOfCooks = 7;
    static bool simulationOn;

public:
    SimulationModel();

    static void getQ();

    static void ovenThread(Oven *oven);

};


#endif
