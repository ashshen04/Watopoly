#include "coop.h"

Coop::Coop(string name, int pos) : NonProperty{name, pos} {}

void Coop::action(Player& p) {
    p.SubMoney(COOP_FEE);
    if (&p == nullptr) return;
    cout << "Player" << p.getChar() << ": Paied $150 Coop Fee to School" << endl;
}
