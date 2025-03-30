#include <iostream>
#include <fstream>
#include <string>
#include "player.h"
using namespace std;

Player::Player(string name, char character, double money, int position) 
    : name{name}, character{character}, money{money}, position{position} {}

string Player::getName() const {
    return name;
}

char Player::getChar() const {
    return character;
}

double Player::getMoney() const {
    return money;
}

int Player::getPosition() const {
    return position;
}

bool Player::getinTims() const {
    return inTims;
}

int Player::getTimsCup() const {
    return timsCups;
}

double Player::getAssets() const {
    int building_money;
    
    for (auto const & building : properties) {
        // ...
    }

    int asset = money + building_money;
    return asset;
}

void Player::changeinTims(bool status) { 
    inTims = status;
}

void Player::outofTims() {
    inTims = false;
    timsTurn = 0;
}

int Player::AddTimsTurn() {
    ++timsTurn;
    return timsTurn;
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

