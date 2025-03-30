// add function add money to the play Player::AddMoney(int money);
// Player::moveto(int pos)

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <fstream>
#include <string>
#include <map>

const int SQUARE_SIZE = 40;
const int OSAP = 200;

class Player {
    string name;
    char character;
    unsigned int money;
    int position;
    map<string, int> properties;
    bool inTims;
    int timsTurn;
    int timsCups;
    int GymNums;
    int ResNums;

    public:
        Player(string name, char character, unsigned int money, int position);

        string getName() const;
        char getChar() const;
        unsigned int getMoney() const;
        int getPosition() const;
        int getTimsCup() const;
        int getAssets() const;
        bool getinTims() const;
        void changeinTims(bool status);
        void outofTims();
        int AddTimsTurn(); // add and return the timsturn
        void improve(string property);
        void trade(char c, string give, string receive);
        void mortgage(string property);
        void unmortgage(string property);
        void bankrupt(); // consider removing this and add a bankrupt() under game
        void assets();
        void all();
        void notifyObservers();
        void AddMoney(int added);
        void SubMoney(int subed);
        void moveto(int pos); // move from osap
        void move(int pos); // move from the original position
        void AddTimsCup();
        void UseTimsCup();

        ~Player();

};

#endif
