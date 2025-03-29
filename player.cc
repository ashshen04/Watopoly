#include <iostream>
#include <fstream>
#include <string>
#include "player.h"
using namespace std;

Player::Player(string name, char character, unsigned int money, int position) 
    : name{name}, character{character}, money{money}, position{position} {}

string Player::getName() {
    return name;
}

char Player::getChar() {
    return character;
}

unsigned int Player::getMoney() {
    return money;
}

void Player::improve(string property) {
    if (properties.at(property)) {
        ++properties.at(property);
        cout << property << "is improved! It now has" << properties.at(property) << "improvements" << endl;
    } else {
        cout << "Error: Improve Property that is not owned!" << endl;
    }

}

void Player::trade(char c, string give, string receive) {
    
}

void Player::mortgage(string property) {}

void Player::unmortgage(string property) {}

void Player::bankrupt() {
    
}

void Player::assets() {
    int asset;
    
    // add situation of not called after Tuition
}

void Player::all() {}

void Player::notifyObservers() {}

void Player::AddMoney(int added) {
    money += added;
}

void Player::SubMoney(int subed) {
    // lead to option of mortgage ...
}

void Player::moveto(int pos) {
    position = pos;
}

void Player::move(int pos) {
    int tmp = position + pos;
    if (tmp > SQUARE_SIZE) { // ie >40 for basic watopoly
        AddMoney(OSAP);
        cout << "Passed by OSAP!!! $200 is added for you!" << endl;
    }
    position = tmp % SQUARE_SIZE;
}

void Player::AddTimsCup() {
    ++timsCups;
}

void Player::UseTimsCup() {
    --timsCups;
}

Player::~Player() {}

