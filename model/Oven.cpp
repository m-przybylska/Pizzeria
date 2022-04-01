//
// Created by Magda on 25.03.2022.
//

#include "Oven.h"

Oven::Oven() {}

Oven::~Oven() {

}

void Oven::putIn() {
    std::lock_guard<std::mutex> guard(notBakedMutex);
}

int Oven::takeOut() {
    int takenOut = 0;
    std::lock_guard<std::mutex> guard(notBakedMutex);
    for (auto it = notBaked.begin(); it != notBaked.end(); ++it){
        if ( it->timeDoEndBacking <= 0){
            takenOut++;
            notBaked.erase(it);
            --it;
        }
    }
    return takenOut;
}

void Oven::bakeAll() {
    if(notBaked.size() < 5) {
        std::lock_guard <std::mutex> guard(notBakedMutex);
        for (pizza &pizza: notBaked) {
            pizza.bake();
        }
    }
}

void Oven::live(){
    functioning = true;
    while (functioning){
        bakeAll();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Oven::stop() {
    functioning = false;
}

int Oven::getRemainingTime(int i){
    std::lock_guard<std::mutex> guard(notBakedMutex);
    return notBaked[i].timeDoEndBacking;
}

int Oven::getSize(){
    std::lock_guard<std::mutex> guard(notBakedMutex);
    return notBaked.size();
}