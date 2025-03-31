#ifndef COOP_H
#define COOP_H
#include <iostream>
#include "player.h"
#include "nonproperty.h"
using namespace std;

class Coop : public NonProperty {
        const int COOP_FEE = 150;
    public:
        Coop(string name, int pos);
        void action(Player& p) override;
};

#endif
