// add function add money to the play Player::AddMoney(int money);
// Player::moveto(int pos)

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "property.h"

class Player {
    string name;
    char character;
    unsigned int money;
    int position;
    map<string, int> properties;
    bool inTims;
    int timsCups;
    int GymNums;
    int ResNums;

    public:
        Player(string name, char character, unsigned int money, int position);

        string getName();
        char getChar();
        unsigned int getMoney();
        void improve(Property property);
        void trade(char c, string give, string receive);
        void mortgage(Property property);
        void unmortgage(Property property);
        void bankrupt(); // consider removing this and add a bankrupt() under game
        void assets();
        void all();
        void notifyObservers();
        void AddMoney(int added);
        void SubMoney(int subed);
        void moveto(int pos); // move from osap
        void mvoe(int pos); // move from the original position

        ~Player();

};

#endif
