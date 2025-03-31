#include "dice.h"
#include "const.h"
#include <cstdlib> // standard library for rand()
#include <ctime> // for time()
using namespace std;

const int DICE_MIN = 1;
const int DICE_MAX = 6;

int Dice::roll() {
    srand(time(0)); // using current time for random generate
    dice1 = rand() % DICE_MAX + DICE_MIN;
    dice2 = rand() % DICE_MAX + DICE_MIN;
    cout << "You rolled " << dice1 + dice2 << endl;
    cout << "Dice1: " << dice1 << endl;
    cout << "Dice2: " << dice2 << endl;
    return dice1 + dice2;
}

int Dice::testroll(int d1, int d2) {
    dice1 = d1;
    dice2 = d2;
    cout << "You rolled " << dice1 + dice2 << endl;
    cout << "Dice1: " << dice1 << endl;
    cout << "Dice2: " << dice2 << endl;
    return dice1 + dice2;
}

bool Dice::isDouble() {
    return dice1 == dice2;
}

