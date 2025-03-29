#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
using namespace std;

class Player;

class Game {
    vector<Player> players;
    vector<shared_ptr<Player>> currPlayer;

    public:
    Game(vector<Player> players, vector<shared_ptr<Player>> currPlayer);
    void AddPlayer(Player& player);
};

#endif