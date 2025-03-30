#ifndef TIMSLINE_H
#define TIMSLINE_H
#include "player.h"
#include "nonproperty.h"
using namespace std;

class TimsLine : public NonProperty {
    public:
        TimsLine(string name, int pos) : NonProperty{name, pos} {}
        void action(Player& p) override {
            
        }
};

#endif