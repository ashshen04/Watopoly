#ifndef TIMSLINE_H
#define TIMSLINE_H
#include <iostream>
#include <string>
#include "dice.h"
#include "rolluprimcup.h"
#include "player.h"
#include "nonproperty.h"
using namespace std;

class TimsLine : public NonProperty {
    public:
        TimsLine(string name, int pos);
        void action(Player& p) override;
        void LineAction(Player &p, Dice &dice);

    private:
        void leaveLine(Player &p, Dice &dice);
};

#endif

