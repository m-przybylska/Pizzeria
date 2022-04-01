//
// Created by Magda on 25.03.2022.
//

#include "Sink.h"

Sink::Sink() {}

Sink::~Sink() {

}

void Sink::startUsing(){
    isLocked = true;
}

void Sink::stopUsing(){
    isLocked = false;
}

bool Sink::isBeingUsed(){
    return isLocked;
}