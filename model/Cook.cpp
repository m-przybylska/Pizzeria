//
// Created by Magda on 25.03.2022.
//

#include "Cook.h"

Cook::Cook() {
    this->numberOfCook = this->numberOfCooks++;
    actuallyProducing = -1;
    isAlive = false;
    action = WAIT;
    progress = 0;
}

Cook::~Cook() {
    if (life.joinable()){
        life.join();
    }
}

void Cook::useSink(Sink *sink){
    action = WAIT;

    actuallyProducing = random(0, typesOfBakedGoods-1);

    queueSinkMutex.lock();
    queueSink.push_back(numberOfCook);
    queueSinkMutex.unlock();

    {
        std::unique_lock<std::mutex> lck(queueSinkMutex);
        queueSinkCV.wait(lck, [this] { return queueSink.front() == this->numberOfCook || !this->isAlive; });
    }

    if (!isAlive){
        queueSinkCV.notify_all();
        return;
    }

    sink->startUsing();
    action = SINK;
    sleep(500,2000);
    sink->stopUsing();

    action = WAIT;

    queueSinkMutex.lock();
    queueSink.pop_front();
    queueSinkMutex.unlock();

    queueSinkCV.notify_all();

}

void Cook::useWorktop(Worktop *worktop){
    action = WAIT;

    queueWorktopMutex.lock();
    queueWorktop.push_back(numberOfCook);
    queueWorktopMutex.unlock();

    {
        std::unique_lock<std::mutex> lck(queueWorktopMutex);
        queueWorktopCV.wait(lck, [this] { return queueWorktop.front() == this->numberOfCook || !this->isAlive; });
    }

    if (!isAlive){
        queueWorktopCV.notify_all();
        return;
    }


    worktop->startUsing();
    action = WORKTOP;
    sleep(1000,3000);
    worktop->stopUsing();

    action = WAIT;

    queueWorktopMutex.lock();
    queueWorktop.pop_front();
    queueWorktopMutex.unlock();

    queueWorktopCV.notify_all();
}

void Cook::useOven(Oven *oven){
    action = WAIT;

    queueOvenMutex.lock();
    queueOven.push_back(id);
    queueOvenMutex.unlock();

    {
        std::unique_lock<std::mutex> lck(queueOvenMutex);
        queueOvenCV.wait(lck, [this] { return queueOven.front() == this->numberOfCook || !this->isAlive; });
    }

    if (!isAlive){
        queueOvenCV.notify_all();
        return;
    }

    oven->putIn(actuallyProducing);
    action = OVEN;
    sleep(500,1000);
    for (int i = 0; i < typesOfBakedGoods; i++){
        numberOfBakedGoods[i] = oven->takeOut(i);
    }
    action = WAIT;

    queueOvenMutex.lock();
    queueOven.pop_front();
    queueOvenMutex.unlock();

    queueOvenCV.notify_all();
}

void Cook::useShelf(Shelf *shelf){
    action = SHELF;
    for (int i = 0; i < typesOfBakedGoods; i++){
        shelf->addBread(i,numberOfBakedGoods[i]);
        numberOfBakedGoods[i] = 0;
        sleep(100,500);
    }
    action = WAIT;
}

void Cook::sleep(int min, int max){
    int s = random(min,max)/100;
    for (int i = 0; i < s; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->progress = 100*i/s;

        if (!this->isAlive) {
            return;
        }
    }
}

void Cook::live(Sink *sink, Worktop *worktop, Oven* oven, Shelf* shelf){
    while(this->isAlive){
        action = WAIT;
        useSink(sink);
        useWorktop(worktop);
        useOven(oven);
        useShelf(shelf);
    }
}

int Cook::getNumberOfCook() const{
    return numberOfCook;
}

int Cook::getIsAlive() const{
    return isAlive;
}

string Cook::getAction(){
    return cookActionTag[action];
}

int Cook::getProgress() const{
    return progress;
}

int Cook::getActuallyProducing() const{
    RETURN actuallyProducing;
}

void Cook::start(Sink *sink, Worktop *worktop, Oven* oven, Shelf* shelf){
    isAlive = true;
    life = std::thread(&Cook::live, this, sink, worktop, oven, shelf);
}

void Cook::stop(){
    isAlive = false;
}
