#ifndef GOTOTIMS_H
#define GOTOTIMS_H
#include <iostream>
#include "const.h"
#include "nonproperty.h"
#include "player.h"
using namespace std;

class GotoTims : public NonProperty {
    public:
        GotoTims(string name, int pos) : NonProperty{name, pos} {}
        void action(Player& p) override {
            p.moveto(TIMSLINE_POS);
            p.changeinTims(true);
            cout << "Player" << p.getChar() << " : You are sent to DC Tims Line square" << endl;
        }
};


#endif