#ifndef GOTOTIMS_H
#define GOTOTIMS_H
#include <iostream>
#include "const.h"
#include "nonproperty.h"
#include "player.h"
using namespace std;

class GotoTims : public NonProperty {
    public:
        GotoTims(string name, int pos);
        void action(Player& p) override;
};


#endif