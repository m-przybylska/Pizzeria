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

int Shelf::take(int amount) {

    if (pizzas - amount > 0) {
        pizzas-=amount;
        return amount;
    }else{
        amount = pizzas;
        pizzas = 0;
        return amount;
    }
    return 0;
}

int Shelf::get() {
    return pizzas;
}
