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
    vector<Player> players;
    vector<shared_ptr<Player>> currPlayer;
    vector<shared_ptr<Property>> properties;
    Dice * dice;
    Board * board;

    public:
    Game(vector<Player> players, shared_ptr<Player> currPlayer);
    
    void AddPlayer(Player& player);
    void StartGame();
    void EndGame();
    void SaveGame(ofstream &file);
    void LoadGame();
    void nextPlayer();
    void movePlayer();
    shared_ptr<Player> findPlayer(string name);
};

#endif