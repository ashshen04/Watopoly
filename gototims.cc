#include "gototims.h"

GotoTims::GotoTims(string name, int pos) : NonProperty{name, pos} {}

void GotoTims::action(Player& p) {
    p.moveto(TIMSLINE_POS);
    p.changeinTims(true);
    cout << "Player" << p.getChar() << " : You are sent to DC Tims Line square" << endl;
}
