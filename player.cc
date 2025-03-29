#include "player.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Player::Player(string name, char character, unsigned int money, int position) 
    : name{name}, character{character}, money{money}, position{position} {}

string Player::getName() {
    return name;
}

char getChar() {
    return character;
}

unsigned int getMoney() {
    return money;
}

void improve(string property) {
    properties.at();
}

void trade(char c, string give, string receive) {
    
}

void mortgage(Property property);

void unmortgage(Property property);

void bankrupt() {
    
}

void assets() {
    
    // add situation of not called after Tuition
}

void all() 

void notifyObservers()

void AddMoney(int added) {
    money += added;
}

void SubMoney(int subed) {
    // lead to option of mortgage ...
}

void moveto(int pos) {
    position = pos;
}

void move(int pos) {
    position += pos;
}

~Player();

