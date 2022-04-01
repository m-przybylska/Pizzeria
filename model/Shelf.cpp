//
// Created by Magda on 25.03.2022.
//

#include "Shelf.h"

Shelf::Shelf() {

}

Shelf::~Shelf() {

}

void Shelf::add(int amount) {
    pizzas += amount;
}

bool Shelf::take() {
    if (pizzas > 0) {
        pizzas--;
        return true;
    }
    return false;
}

int Shelf::get() {
    return pizzas;
}
