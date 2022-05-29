//
// Created by Magda on 25.03.2022.
//

#ifndef UNTITLED4_DELIVERYMAN_H
#define UNTITLED4_DELIVERYMAN_H

#include <thread>
#include <mutex>
#include <atomic>
#include <deque>
#include <mutex>
#include <condition_variable>
#include "ThermalBag.h"
#include "Shelf.h"

class DeliveryMan {
    enum deliveryManAction {
        ADD,
        GO,
        WAIT
    };
    const std::string deliveryManActionTag[3] = {"add", "go", "wait"};

    int id = -1;
    std::thread life;
    std::atomic<bool> isAlive;

    std::mutex mutexThermalBag;
    static std::condition_variable queueThermalBagCV;
    static int numberOfDeliveryMan;


public:
    std::atomic<deliveryManAction> action;

    static std::deque<int> queueThermalBag;

    DeliveryMan();

    DeliveryMan(const DeliveryMan &deliveryMan);

    virtual ~DeliveryMan();

    void live(ThermalBag *thermalBag, Shelf *shelf);

    void stop();

    void start(ThermalBag *thermalBag, Shelf *shelf);

    int getNumberOfDeliveryMan();

    std::string getAction();

    void useThermalBag(ThermalBag *thermalBag, Shelf *shelf);

    void go();

    void sleep(int min, int max);

    int random(int min, int max);

};


#endif
