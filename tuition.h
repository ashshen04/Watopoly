#ifndef TUITION_H
#define TUITION_H
#include <iostream>
#include <string>
#include "nonproperty.h"
#include "player.h"
using namespace std;

class Tuition : public NonProperty {
    const int const_tuition = 300;
    public:
        Tuition(const string& name, int position);
        void action(Player& p) override;
};

#endif

