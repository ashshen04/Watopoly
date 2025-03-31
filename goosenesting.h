#ifndef GOOSENESTING_H
#define GOOSENESTING_H
#include <iostream>
#include "nonproperty.h"
#include "player.h"
using namespace std;

class GooseNesting : public NonProperty {
    public:
        GooseNesting(const string name, int pos);
        void action(Player& p) override;
};

#endif