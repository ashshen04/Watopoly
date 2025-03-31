#include "goosenesting.h"

GooseNesting::GooseNesting(const string name, int pos) : NonProperty{name, pos} {}

void GooseNesting::action(Player& p) {
    cout << "Player" << p.getChar() << " : You are ATTACKED by a flock of nesting geese!" << endl;
}
