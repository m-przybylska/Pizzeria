//
// Created by Magda on 25.03.2022.
//

#ifndef UNTITLED4_SINK_H
#define UNTITLED4_SINK_H


class Sink {
    bool isLocked = false;

public:
    Sink();

    virtual ~Sink();

    void startUsing();

    void stopUsing();

    bool isBeingUsed();

};


#endif
