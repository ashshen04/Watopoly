#ifndef ROLLUPRIMCUP_H
#define ROLLUPRIMCUP_H
#include <iostream>
#include "player.h"
#include "nonproperty.h"
using namespace std;

class RollUpRimCup : public NonProperty {
    static int ActiveCount = 0;
    const int MaxCup = 4;
    
    public:
        static void getCup(Player &p);
        static void useCup();
};

#endif