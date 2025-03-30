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
    void StartGame();
    void EndGame();
    void SaveGame(ofstream &file);
    void LoadGame();
    void nextPlayer();
    void movePlayer();
    shared_ptr<Player> findPlayer(char c);
};

#endif