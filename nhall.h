#ifndef NHALL_H
#define NHALL_H
#include <iostream>
#include "player.h"
#include "nonproperty.h"
#include "rolluprimcup.h"
using namespace std;


class NHall : public NonProperty {
    public:
        NHall();
        void action(Player& p) override {
            
        }
        ~NHall();
};

#endif