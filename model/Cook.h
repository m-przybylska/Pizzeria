//
// Created by Magda on 25.03.2022.
//

#ifndef UNTITLED4_COOK_H
#define UNTITLED4_COOK_H

#include <thread>
#include <string>
#include <atomic>
#include <deque>
#include <condition_variable>
#include "Oven.h"
#include "Shelf.h"
#include "Sink.h"
#include "Worktop.h"

using namespace std;

class Cook {

    enum cookAction{
        SINK,
        WORKTOP,
        OVEN,
        SHELF,
        WAIT
    };

    const std::string cookActionTag[5] = {"sink", "worktop", "oven", "shelf", "wait"};

    static condition_variable queueSinkCV;
    static condition_variable queueWorktopCV;
    static condition_variable queueOvenCV;

    static int numberOfCooks; 
    int numberOfBaked;

    atomic<bool> isAlive;
    int numberOfCook = -1;
    thread life;

    atomic<cookAction> action;
    atomic<int> progress;

public:
    static deque<int> queueSink;
    static deque<int> queueWorktop;
    static deque<int> queueOven;

    Cook();
    Cook(const Cook& cook);
    virtual ~Cook();

    void useSink(Sink *sink);
    void useWorktop(Worktop *worktop);
    void useOven(Oven *oven);
    void useShelf(Shelf *shelf);

    void sleep(int min, int max);
    int random(int min, int max);
    void live(Sink *sink, Worktop *worktop, Oven* oven, Shelf* shelf);

    int getNumberOfCook() const;
    int getIsAlive() const;
    std::string getAction();
    int getProgress() const;
    int getActuallyProducing() const;

    void start(Sink *sink, Worktop *worktop, Oven* oven, Shelf* shelf);
    void stop();

};
#endif
