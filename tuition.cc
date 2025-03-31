#include "tuition.h"
#include "player.h"
#include <iostream>
#include <memory>

using namespace std;

Tuition::Tuition(const string& name, int position) : NonProperty{name, position} {}

void Tuition::action(Player& p) {
    cout << "You need to pay Tuition! Choose between Option1 and Option2:" << endl;
    cout << "Option1: $300" << endl;
    cout << "Option2: 10%% of your total worth" << endl;

    string in;
    while (cin >> in) {
        if (in == "Option1") {
            p.SubMoney(const_tuition);
            cout << "You have paid $300 tuition as your tuition" << endl;
            break;
        } else if (in == "Option2") {
            int percentage_tuition = static_cast<int> (p.getAssets() * 0.1);
            p.SubMoney(percentage_tuition);
            cout << "You have paid 10%" << "of your total worth as your tuition" << endl;
            break;
        } else {
            cout << "Error: Invalid input. Please re-enter Option1 or Option2" << endl;
        }
    }
}