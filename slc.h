#ifndef SLC_H
#define SLC_H
#include <iostream>
#include <cstdlib>
#include "const.h"
#include "player.h"
#include "nonproperty.h"
#include "rolluprimcup.h"
using namespace std;


class SLC : public NonProperty {
    RollUpRimCup* check;
    public:
        SLC(string name, int pos) : NonProperty{name, pos}, check{nullptr} {}
        void action(Player& p) override {
            cout << "Player" << p.getChar() << " arrived at SLC! " << endl;
            check->getCup(p);
            
            int random = rand() % 24;
            int move = 0;

            if (random < 3) move = -3; // 0,1,2
            else if (random < 7) move = -2; // 3,4,5,6
            else if (random < 11) move = -1; // 7,8,9,10
            else if (random < 14) move = 1;
            else if (random < 18) move = 2;
            else if (random < 22) move = 3;
            else if (random == 22) {
                p.moveto(TIMSLINE_POS);
                p.changeinTims(true);
                cout << "Player" << p.getChar() << "is now sent to DC Tims Line :(" << endl;
                return;
            } else { // random == 23
                p.moveto(OSAP_POS);
                p.AddMoney(200);
                cout << "Player" << p.getChar() << "is now sent to OSAP and received $200! Lucky :)" << endl;
                return;
            }

            p.move(move);
            cout << "Player" << p.getChar() << "moves" << move << "space(s)" << endl;
        }
};

#endif