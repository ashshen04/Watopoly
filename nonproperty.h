#ifndef NONPROPERTY_H
#define NONPROPERTY_H
#include "square.h"
using namespace std;

class Square;

class NonProperty : public Square {
    public:
        NonProperty(const string name, int position) : Square{name, position} {}
        void action(Player& p) override = 0;
        virtual ~NonProperty() = default;
};

#endif