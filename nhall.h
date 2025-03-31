#ifndef NHALL_H
#define NHALL_H
#include <iostream>
#include "player.h"
#include "nonproperty.h"
#include "rolluprimcup.h"
using namespace std;


class NHall : public NonProperty {
    RollUpRimCup* check;
    public:
        NHall(string name, int pos);
        void action(Player& p) override;
};

#endif
