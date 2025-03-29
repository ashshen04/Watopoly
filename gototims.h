#ifndef GOTOTIMS_H
#define GOTOTIMS_H
#include <iostream>
#include "nonproperty.h"
#include "player.h"
using namespace std;

class GotoTims : public NonProperty {
    const int TIMSLINE_POS = 10;
public:
    void action(Player& p) {
        p.moveto(TIMSLINE_POS);
        cout << "Player" << p.getChar() << " : You are moved to DC Tims Line square" << endl;
    }
};


#endif