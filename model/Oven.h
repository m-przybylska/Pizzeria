//
// Created by Magda on 25.03.2022.
//

#ifndef UNTITLED4_OVEN_H
#define UNTITLED4_OVEN_H
#include <thread>
#include <mutex>
#include <vector>

class Oven{
        struct pizza {
            int timeDoEndBacking;

            void bake(){
                if (this-> timeDoEndBacking > 0)
                    this->timeDoEndBacking -= 100;
            }
        };

private:
    const int maxAmmout = 4;
    const int bakeTime = 5000;
    std::mutex notBakedMutex;
    std::vector<pizza> notBaked;
    bool functioning = true;


public:
    Oven();

    virtual ~Oven();

    void putIn();

    int takeOut();

    void bakeAll();

    void live();

    void stop();

    int getRemainingTime(int i);

    int getType(int i);

    int getSize();
};


#endif
