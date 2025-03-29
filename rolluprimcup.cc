#include "rolluprimcup.h"
#include <iostream>
using namespace std;

void RollUpRimCup::getCup(Player &p) {
    if (ActiveCount < MaxCup) {
        p.AddTimsCup();
        ++ActiveCount;
    }
}

void RollUpRimCup::useCup() {
    if (ActiveCount > 0) {
        --ActiveCount;
    }
}
