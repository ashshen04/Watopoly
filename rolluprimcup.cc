#include "rolluprimcup.h"
#include <iostream>
using namespace std;


void RollUpRimCup::getCup(Player &p) {
    if (ActiveCount < MaxCup) {
        bool able = ((rand() % 100) == 0); // 0.01 chance
        if (able) {
            p.AddTimsCup();
            ++ActiveCount;
            cout << "Congrats! You got a TimsCup!!!" << endl;
        }
    }
}

void RollUpRimCup::useCup(Player &p) {
    if (ActiveCount > 0 && p.getTimsCup() > 0) {
        p.UseTimsCup();
        --ActiveCount;
    }
}

int RollUpRimCup::ActiveCount = 0;
