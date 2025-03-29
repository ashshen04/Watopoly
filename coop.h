#ifndef COOP_H
#define COOP_H
#include <iostream>
#include "player.h"
#include "nonproperty.h"
using namespace std;


class OSAP : public NonProperty {
        const int COOP_FEE = 150;
    public:
        void action(Player& p) {
            p.SubMoney(COOP_FEE);
            cout << "Player" << p.getChar() << ": Paied $150 Coop Fee to School" << endl;
        }
};

#endif