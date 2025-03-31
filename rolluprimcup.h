#ifndef ROLLUPRIMCUP_H
#define ROLLUPRIMCUP_H
#include <iostream>
#include <cstdlib>
#include "const.h"
#include "player.h"
#include "nonproperty.h"
using namespace std;

class RollUpRimCup : public NonProperty {
    static int ActiveCount;
    
    public:
        static void getCup(Player &p);
        static void useCup(Player &p);
};

#endif
