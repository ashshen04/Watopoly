#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "subject.h"

const int SQUARE_SIZE = 40;
const int OSAP = 200;

class Game;
class Property;

class Player : public Subject, public std::enable_shared_from_this<Player> {
    string name;
    char character;
    double money;
    double assets;
    int position;
    vector<shared_ptr<Property>> properties;
    bool inTims;
    int timsTurn;
    int timsCups;
    Game &game;


    public:
    Player(string name, char character, int timscup, double money, int position, Game &game);
    int GymNums;
    int ResNums;
    double playerImproveCost;

    string getName() const{ return name; };
    char getChar() const{ return character; };
    double getMoney() const{ return money; };
    double getPosition() const{ return position; };
    int getTimsCup() const{return timsCups;};
    double getAssets();
    void printAssets() const{
        cout << "You have " << assets << " in total assets." << endl;
    };
    double getPlayerImproveCost() const { return playerImproveCost; };
    
    //to be implemented
    bool getinTims() const { return inTims; }
    void changeinTims(bool status) { inTims = status; }
    void outofTims();
    int AddTimsTurn(); // add and return the timsturn
    
    void calculateAssets();
    void improve(shared_ptr<Property> property);
    bool trade(shared_ptr<Player> other, int give, shared_ptr<Property> receive);
    bool trade(shared_ptr<Player> other, shared_ptr<Property> give, shared_ptr<Property> receive);
    bool trade(shared_ptr<Player> other, shared_ptr<Property> give, int receive);
    
    void addProperty(shared_ptr<Property> property);
    void removeProperty(shared_ptr<Property> property);

    void AddMoney(double added);
    void SubMoney(double subed);
    double SubMoneyInt(double subed);

    double bankrupt(); // consider removing this and add a bankrupt() under game
    void all();
    
    // add action in move
    void moveto(int pos); // move from osap
    void move(int pos); // move from the original position
    void AddTimsCup(){++timsCups;};
    void UseTimsCup(){--timsCups;};

    ~Player();

};

#endif
