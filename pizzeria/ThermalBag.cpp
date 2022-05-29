//
// Created by Magda on 25.03.2022.
//

#include "ThermalBag.h"

ThermalBag::ThermalBag() {

}

ThermalBag::~ThermalBag() {

}

void ThermalBag::add(int amount) {
    pizzas += amount;

}

bool ThermalBag::take() {
    pizzas = 0;
    return true;
}