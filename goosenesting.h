#ifndef GOOSENESTING_H
#define GOOSENESTING_H
#include <iostream>
#include "nonproperty.h"
#include "player.h"
using namespace std;

class GooseNesting : public NonProperty {
    public:
        void action(Player& p) {
            cout << "Attacked: You are attacked by a flock of nesting geese!" << endl;
        }
};

#endif