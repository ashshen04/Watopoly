#ifndef NONPROPERTY_H
#define NONPROPERTY_H
#include "square.h"
using namespace std;

class NonProperty : public Square{
    public:
        NonProperty(const string name, int position);
        void action(Player& p) override = 0;
};

#endif