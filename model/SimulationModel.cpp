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

const int numberOfCooks = 7;
bool simulationOn = true;

void ovenThread(Oven *oven){
    oven->live();
}

void getQ(){
    char esc = getch();
    while (esc != 'q'){
        esc = getch();
    }
    simulationOn = false;
}

SimulationModel::SimulationModel() {

    Shelf shelf;
    Oven oven;
    Sink sink;
    Worktop worktop;
    Cook cook;

    std::vector<Cook> cooks;
    for (int i = 0; i < numberOfCooks; i++){
        cooks.emplace_back(Cook());
    }

    for (Cook& cook: cooks){
        cook.start(&sink, &worktop, &oven, &shelf);
    }

    std::thread ovenT(ovenThread, &oven);
    std::thread end(getQ);

//    while(simulationOn){
//   }

    for (Cook& cook: cooks){
        cook.stop();
    }

    oven.stop();
    ovenT.join();
    end.join();
}
