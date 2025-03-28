#ifndef GOTOTIMS_H
#define GOTOTIMS_H
#include "nonproperty.h"
#include "player.h"
using namespace std;

class GotoTims : public NonProperty {
    const int TIMSLINE_POS = 10;
public:
    void action(Player& p) {
        p.moveto(TIMSLINE_POS);
    }
};


#endif