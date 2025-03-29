#ifndef OSAP_H
#define OSAP_H
#include <iostream>
#include "player.h"
#include "nonproperty.h"
using namespace std;


class OSAP : public NonProperty {
        const int AMOUNT_ADDED = 200;
    public:
        void action(Player& p) {
            p.AddMoney(AMOUNT_ADDED);
            cout << "Passes over or lands on the Collect OSAP: $200 ADDED to player" << p.getChar() << endl;
        }
};

#endif