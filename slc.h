#ifndef SLC_H
#define SLC_H
#include <iostream>
#include <cstdlib>
#include "const.h"
#include "player.h"
#include "nonproperty.h"
#include "rolluprimcup.h"
using namespace std;


class SLC : public NonProperty {
    RollUpRimCup* check;
    public:
        SLC(string name, int pos);

        void action(Player& p) override;
};

#endif