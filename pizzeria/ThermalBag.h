//
// Created by Magda on 25.03.2022.
//

#ifndef UNTITLED4_THERMALBAG_H
#define UNTITLED4_THERMALBAG_H


class ThermalBag {
    int pizzas;
    const int maxAmount = 20;

public:
    ThermalBag();

    virtual ~ThermalBag();

    void add(int amount);

    bool take();

};


#endif
