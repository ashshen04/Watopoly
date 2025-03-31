#ifndef OSAP_H
#define OSAP_H
#include <iostream>
#include "player.h"
#include "nonproperty.h"
using namespace std;


class OSAP_type : public NonProperty {
    const int AMOUNT_ADDED = 200;
    public:
        OSAP_type(string name, int pos);
        void action(Player& p) override;
};

#endif
