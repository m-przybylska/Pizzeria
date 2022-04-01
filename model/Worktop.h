//
// Created by Magda on 25.03.2022.
//

#ifndef UNTITLED4_WORKTOP_H
#define UNTITLED4_WORKTOP_H


class Worktop {
    bool isLocked = false;

public:
    Worktop();

    virtual ~Worktop();

    void startUsing();
    void stopUsing();
    bool isBeingUsed();

};


#endif
