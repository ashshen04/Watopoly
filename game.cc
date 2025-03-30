#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "game.h"
#include "player.h"
#include "property.h"
using namespace std;

//change needed
Game::Game(vector<Player> players, shared_ptr<Player> currPlayer) : players{players}, currPlayer{currPlayer} {}

void Game::AddPlayer(Player& player) {
    players.emplace_back(player);
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

    for (auto & player : players) {
        file << player.getName() << " " << player.getChar() << " " 
             << player.getMoney() << " " << player.getPosition() << endl;
    }

    for (auto & property : properties) {
        file << property->getName() << " " << property->getOwner()->getName() << " "; 
        if (property->getImproveNum() != 0) file << property->getImproveNum() << endl;
    }

    cout << "Game saved successfully!" << endl;
    
}

void Game::LoadGame() {

}

void Game::nextPlayer() {
    
}

void Game::movePlayer() {
    Dice dice;
    int roll = dice.roll();
    auto land_square = squares[]
}

shared_ptr<Player> Game::findPlayer(string name) {
    return players.at(name);
}
