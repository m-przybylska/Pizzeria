//
// Created by Magda on 25.03.2022.
//

#include "DeliveryMan.h"
#include "Entity.h"
#include <random>
#include <iostream>

using namespace std;

int DeliveryMan::numberOfDeliveryMan = 0;
std::deque<int> DeliveryMan::queueThermalBag;
std::condition_variable DeliveryMan::queueThermalBagCV;

DeliveryMan::DeliveryMan() {
    this->id = this->numberOfDeliveryMan++;
    isAlive = false;
    action = WAIT;
}

DeliveryMan::DeliveryMan(const DeliveryMan &DeliveryMan) {
    this->id = DeliveryMan.id;
}

DeliveryMan::~DeliveryMan() {
    if (life.joinable()) {
        life.join();
    }
}

void DeliveryMan::live(ThermalBag *thermalBag, Shelf *shelf) {
    while (this->isAlive) {
        action = WAIT;
        useThermalBag(thermalBag, shelf);
        go();
    }
}

void DeliveryMan::stop() {
    isAlive = false;
}

std::string DeliveryMan::getAction() {
    return deliveryManActionTag[action];
}

int DeliveryMan::getNumberOfDeliveryMan() {
    return id;
}

void DeliveryMan::start(ThermalBag *thermalBag, Shelf *shelf) {
    isAlive = true;
    life = std::thread(&DeliveryMan::live, this, thermalBag, shelf);
}

void DeliveryMan::useThermalBag(ThermalBag *thermalBag, Shelf *shelf) {
    action = WAIT;
    printAction("Delivery man", getAction(), id);
    mutexThermalBag.lock();
    queueThermalBag.push_back(numberOfDeliveryMan);
    mutexThermalBag.unlock();

    {
        std::unique_lock<std::mutex> lck(mutexThermalBag);
        queueThermalBagCV.wait(lck, [this] {
            return queueThermalBag.front() == this->numberOfDeliveryMan || !this->isAlive;
        });
    }

    if (!isAlive) {
        queueThermalBagCV.notify_all();
        return;
    }

    action = ADD;
    printAction("Delivery man", getAction(), id);

    int adding = shelf->take(20);
    thermalBag->add(adding);
    sleep(500, 2000);

    action = WAIT;
    printAction("Delivery man", getAction(), id);

    mutexThermalBag.lock();
    queueThermalBag.pop_front();
    mutexThermalBag.unlock();

    queueThermalBagCV.notify_all();
}

void DeliveryMan::go() {
    action = GO;
    printAction("Delivery man", getAction(), id);

    sleep(1500, 2500);

    action = WAIT;
    printAction("Delivery man", getAction(), id);
}

int DeliveryMan::random(const int min, const int max) {
    static thread_local mt19937 *generator = nullptr;
    static hash<thread::id> hasher;

    if (!generator) {
        generator = new mt19937(clock() + hasher(this_thread::get_id()));
    }
    uniform_int_distribution<int> distribution(min, max);

    return distribution(*generator);
}

void DeliveryMan::sleep(int min, int max) {
    int s = random(min, max) / 100;

    for (int i = 0; i < s; i++) {
        this_thread::sleep_for(chrono::milliseconds(100));

        if (!this->isAlive) {
            return;
        }
    }
}
