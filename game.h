#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "player.h"
#include "board.h"
#include "dice.h"
#include "square.h"
#include "property.h"
using namespace std;

class Player;

class Game {
    vector<shared_ptr<Player>> players;
    vector<shared_ptr<Player>> currPlayer;
    vector<shared_ptr<Property>> properties;
    Dice * dice;
    Board * board;

    public:
    Game();
    ~Game();

    shared_ptr<Player> getCurrPlayer();
    vector<shared_ptr<Property>> getProperties();
    vector<shared_ptr<Player>> getPlayers();
    void AddPlayer(string name, char character, int timscup, double money, int position);
    void StartGame();
    void EndGame();
    void SaveGame(ofstream &file);
    void nextPlayer();
    void movePlayer();
    void trade();
    void all(); // outputing 
    shared_ptr<Player> findPlayer(string name);
    void removePlayer(shared_ptr<Player> player);

};

#endif