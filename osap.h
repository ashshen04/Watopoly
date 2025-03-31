#ifndef OSAP_H
#define OSAP_H
#include <iostream>
#include "player.h"
#include "nonproperty.h"
using namespace std;


class OSAP : public NonProperty {
    const int AMOUNT_ADDED = 200;
    public:
        OSAP(string name, int pos);
        void action(Player& p) override;
};

#endif
