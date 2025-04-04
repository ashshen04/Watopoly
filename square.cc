#include "square.h"
#include <iostream>
#include <string>
using namespace std;

Square::Square(const string name, int position) : name{name}, position{position} {}

string Square::getName() const {
    return name;
}

int Square::getPosition() const {
    return position;
}

void Square::notify(int playpos, int temp, int a, int b, char c) {
    if (playpos == position) {
        cout << "Player landed on " << name << "!" << endl;

    }
}
