#ifndef NHALL_H
#define NHALL_H
#include <iostream>
#include "player.h"
#include "nonproperty.h"
#include "rolluprimcup.h"
using namespace std;


class NHall : public NonProperty {
    RollUpRimCup* check;
    public:
        NHall(string name, int pos) : NonProperty{name, pos}, check{nullptr} {}
        void action(Player& p) override {
            cout << "Player" << p.getChar() << " arrived at NeedlesHall! " << endl;
            check->getCup(p);
            
            int random = rand() % 18;
            int abs_money_change = 0;

            // sub
            if (random == 0) abs_money_change = 200; 
            else if (random < 2) abs_money_change = 100; 
            else if (random < 5) abs_money_change = 50;

            // add
            else if (random < 11) abs_money_change = 25;
            else if (random < 14) abs_money_change = 50;
            else if (random < 16) abs_money_change = 100;
            else abs_money_change = 200;

            if (random < 11) {
                p.SubMoney(abs_money_change);
                cout << "Player " << p.getChar() << "loses $" << abs_money_change << endl;
            } else {
                p.AddMoney(abs_money_change);
                cout << "Player " << p.getChar() << "gains $" << abs_money_change << endl;
            }
        }    
};

#endif