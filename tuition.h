#ifndef GOOSENESTING_H
#define GOOSENESTING_H
#include <iostream>
#include <string>
#include "nonproperty.h"
#include "player.h"
using namespace std;

class GooseNesting : public NonProperty {
    const int const_tuition = 300;
    public:
        void action(Player& p) override {
            cout << "You need to pay Tuition! Choose between Option1 and Option2:" << endl;
            cout << "Option1: $300" << endl;
            cout << "Option2: 10%% of your total worth" << endl;
            
            string in;
            cin >> in;
            if (in == "Option1") {
                p.SubMoney(const_tuition);
                cout << "You have paid $300 tuition as your tuition" << endl;
            }
            else if (in == "Option2") {
                int percentage_tuition = static_cast<int> (p.assets() * 0.1);
                p.SubMoney(percentage_tuition);
                cout << "You have paid 10%% of your total worth as your tuition" << endl;
            } else {
                cout << "Error: Invalid input. Please re-enter Option1 or Option2" << endl;
            }
        }
};

#endif