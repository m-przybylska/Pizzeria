//
// Created by Magda on 25.03.2022.
//

#include <random>
#include <iostream>
#include "Cook.h"

int Cook::numberOfCooks = 0;
std::deque<int> Cook::queueSink;
std::deque<int> Cook::queueWorktop;
std::deque<int> Cook::queueOven;
std::condition_variable Cook::queueSinkCV;
std::condition_variable Cook::queueWorktopCV;
std::condition_variable Cook::queueOvenCV;

using namespace std;

Cook::Cook() {
    this->numberOfCook = this->numberOfCooks++;
    isAlive = false;
    action = WAIT;
    progress = 0;
    numberOfBaked = 0;
}

Cook::Cook(const Cook &Cook) {
    this->numberOfCook = Cook.numberOfCook;
}

Cook::~Cook() {
    if (life.joinable()) {
        life.join();
    }
}

void Cook::useSink(Sink *sink) {
    action = WAIT;
    //cout<< numberOfCook + " : " +getAction()<< endl;

    mutexSink.lock();
    queueSink.push_back(numberOfCook);
    mutexSink.unlock();

     {
         std::unique_lock<std::mutex> lck(mutexSink);
         queueSinkCV.wait(lck, [this] { return queueSink.front() == this->numberOfCook || !this->isAlive; });
     }

    if (!isAlive) {
        queueSinkCV.notify_all();
        return;
    }

    sink->startUsing();
    action = SINK;
    sleep(500, 2000);
    cout<< numberOfCook + " : " +getAction()<< endl;
    sink->stopUsing();

    action = WAIT;

    mutexSink.lock();
    queueSink.pop_front();
    mutexSink.unlock();

    queueSinkCV.notify_all();
}

void Cook::useWorktop(Worktop *worktop) {
    action = WAIT;

    mutexWorktop.lock();
    queueWorktop.push_back(numberOfCook);
    mutexWorktop.unlock();

     {
         std::unique_lock<std::mutex> lck(mutexWorktop);
         queueWorktopCV.wait(lck, [this] { return queueWorktop.front() == this->numberOfCook || !this->isAlive; });
     }

    if (!isAlive) {
        queueWorktopCV.notify_all();
        return;
    }


    worktop->startUsing();
    action = WORKTOP;

    sleep(1000, 3000);
    cout<< this->numberOfCook + " : " +getAction()<< endl;
    worktop->stopUsing();

    action = WAIT;

    mutexWorktop.lock();
    queueWorktop.pop_front();
    mutexWorktop.unlock();

    queueWorktopCV.notify_all();
}

void Cook::useOven(Oven *oven) {
    action = WAIT;
    //cout<< getNumberOfCook() + " : " +getAction()<< endl;

    mutexOven.lock();
    queueOven.push_back(numberOfCook);
    mutexOven.unlock();

     {
         std::unique_lock<std::mutex> lck(mutexOven);
         queueOvenCV.wait(lck, [this] { return queueOven.front() == this->numberOfCook || !this->isAlive; });
     }

    if (!isAlive) {
        queueOvenCV.notify_all();
        return;
    }

    oven->putIn();
    action = OVEN;
    sleep(500, 1000);
    cout<< this->getNumberOfCook() + " : " +getAction()<< endl;

    oven->takeOut();
    action = WAIT;
    //cout<< getNumberOfCook() + " : " +getAction()<< endl;

    mutexOven.lock();
    queueOven.pop_front();
    mutexOven.unlock();

    queueOvenCV.notify_all();
}

void Cook::useShelf(Shelf *shelf) {
    action = SHELF;
    cout<< numberOfCook + " : " +getAction()<< endl;

    shelf->add(1);
    sleep(100, 500);
    action = WAIT;
}

int Cook::random(const int min, const int max) {
    static thread_local mt19937 *generator = nullptr;
    static hash<thread::id> hasher;

    if (!generator) {
        generator = new mt19937(clock() + hasher(this_thread::get_id()));
    }
    uniform_int_distribution<int> distribution(min, max);

    return distribution(*generator);
}

void Cook::sleep(int min, int max) {
    int s = random(min, max) / 100;

    for (int i = 0; i < s; i++) {
        this_thread::sleep_for(chrono::milliseconds(100));
        this->progress = 100 * i / s;

        if (!this->isAlive) {
            return;
        }
    }
}

void Cook::live(Sink *sink, Worktop *worktop, Oven *oven, Shelf *shelf) {
    while (this->isAlive) {
        action = WAIT;
        useSink(sink);
        useWorktop(worktop);
        useOven(oven);
        useShelf(shelf);
    }
}

int Cook::getNumberOfCook() const {
    return numberOfCook;
}

int Cook::getIsAlive() const {
    return isAlive;
}

string Cook::getAction() {
    return cookActionTag[action];
}

int Cook::getProgress() const {
    return progress;
}

void Cook::start(Sink *sink, Worktop *worktop, Oven *oven, Shelf *shelf) {
    isAlive = true;
    life = std::thread(&Cook::live, this, sink, worktop, oven, shelf);
}

void Cook::stop() {
    isAlive = false;
}
