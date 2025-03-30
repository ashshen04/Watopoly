#ifndef GOOSENESTING_H
#define GOOSENESTING_H
#include <iostream>
#include "nonproperty.h"
#include "player.h"
using namespace std;

class GooseNesting : public NonProperty {
    public:
        GooseNesting(const string name, int pos) : NonProperty{name, pos} {}
        void action(Player& p) {
            cout << "Player" << p.getChar() << " : You are ATTACKED by a flock of nesting geese!" << endl;
        }
};

#endif