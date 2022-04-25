//
// Created by Magda on 25.03.2022.
//

#include "Worktop.h"

Worktop::Worktop() {}

Worktop::~Worktop() {

}

void Worktop::startUsing() {
    isLocked = true;
}

void Worktop::stopUsing() {
    isLocked = false;
}

bool Worktop::isBeingUsed() {
    return isLocked;
}