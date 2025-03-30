#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "game.h"
#include "player.h"
#include "property.h"
using namespace std;

Game::Game(vector<Player> players, shared_ptr<Player> currPlayer, Dice &dice, Board &board) 
    : players{players}, currPlayer{currPlayer}, dice{&dice}, board{&board} {
        for (auto& player : players) {
            players.emplace_back(player);
        }
    }

void Game::AddPlayer(Player& player) {
    players.emplace_back(player);
}

void Game::StartGame() {
    cout << "Game has started!" << endl;
    board->drawBoard(cout);
}

void Game::EndGame() {
    cout << "Game has ended!" << endl;
}

void Game::SaveGame(ofstream &file) {
    if (!file) {
        cerr << "Error: Invalid save file" << endl;
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

void Game::nextPlayer() {
    auto it = 
}

void Game::movePlayer() {
    Dice dice;
    int roll = dice.roll();
    
}

shared_ptr<Player> Game::findPlayer(string name) {
    auto it = players.find(name);

}
