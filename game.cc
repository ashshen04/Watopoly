#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "game.h"
#include "player.h"
using namespace std;

Game::Game(vector<Player> players, vector<shared_ptr<Player>> currPlayer) : players{players}, currPlayer{currPlayer} {}

void Game::AddPlayer(Player& player) {
    players.push_back(player);
}

void Game::StartGame() {
    cout << "Game has started!" << endl;
}

void Game::EndGame() {
    cout << "Game has ended!" << endl;
}

void Game::SaveGame(ofstream &file) {
    if (!file) {
        cout << "Error: Invalid save file" << endl;
        return;
    }

    file << players.size() << endl;

    for (auto &player : players) {
        file << player.getName() << " " << player.getChar() << " " 
             << player.getMoney() << " " << player.getPosition() << endl;
    }

    cout << "Game saved successfully!" << endl;
    
}

void LoadGame();

void nextPlayer();

void movePlayer();

shared_ptr<Player> findPlayer(char c);
