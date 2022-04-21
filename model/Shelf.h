//
// Created by Magda on 25.03.2022.
//

#ifndef UNTITLED4_SHELF_H
#define UNTITLED4_SHELF_H


class Shelf {
    int pizzas;

public:
    Shelf();

    virtual ~Shelf();

    void add(int amount);

    int take(int amount);

    int get();

};


#endif
