#include "osap.h"
#include <iostream>

OSAP::OSAP(string name, int pos) : NonProperty{name, pos} {}

void OSAP::action(Player& p) {
    p.AddMoney(AMOUNT_ADDED);
    cout << "Passes over or lands on the Collect OSAP: $200 ADDED to player" << p.getChar() << endl;
}
