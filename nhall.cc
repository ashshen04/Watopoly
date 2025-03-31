#include "nhall.h"
#include <iostream>
using namespace std;

NHall::NHall(string name, int pos) : NonProperty{name, pos}, check{nullptr} {}

void NHall::action(Player& p) {
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
        if (&p == nullptr) return;
    } else {
        p.AddMoney(abs_money_change);
        cout << "Player " << p.getChar() << "gains $" << abs_money_change << endl;
    }
}   
