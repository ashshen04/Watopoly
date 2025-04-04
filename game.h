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
    public:
    vector<shared_ptr<Player>> players;
    vector<shared_ptr<Player>> currPlayer;
    vector<shared_ptr<Property>> properties;
    unique_ptr<Dice> dice;
    vector<shared_ptr<Square>> squares;
    unique_ptr<Board> board;

    public:
    Game();
    ~Game() = default;

    shared_ptr<Player> getCurrPlayer();
    vector<shared_ptr<Property>> getProperties();
    vector<shared_ptr<Player>> getPlayers();
    void AddPlayer(string name, char character, int timscup, double money, int position);
    void AddProperty(string property_name, string owner, int improvements);
    void StartGame();
    void EndGame();
    void SaveGame(ofstream &file);
    void nextPlayer();
    void movePlayer();
    void trade();
    void all(); // outputing 
    shared_ptr<Player> findPlayer(string name);
    void removePlayer(shared_ptr<Player> player);
    void setSquares(vector<shared_ptr<Square>> s){ squares = s;};
    void setProperties (vector<shared_ptr<Property>> s){ properties = s;};
    void movePlayer_test();
    
    bool checkend();

};

#endif
