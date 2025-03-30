#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "const.h"
#include "game.h"
#include "player.h"
#include "property.h"
using namespace std;

Game::Game() {
    dice = new Dice();
    board = new Board();
}

Game::~Game() {
    delete dice;
    delete board;
}

shared_ptr<Player> Game::getCurrPlayer() {
    if (!currPlayer.empty()) {
        return currPlayer[0];
    }
    return nullptr;
}

vector<shared_ptr<Property>> Game::getProperties() {
    return properties;
}

void Game::AddPlayer(Player& player) {
    players.emplace_back(player);
}

void Game::StartGame() {
    if (players.empty()) {
        cout << "No players added to the game!" << endl;
        return;
    }
    cout << "Game started with " << players.size() << " players!" << endl;
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
    if (currPlayer.empty()) return;
    auto first = currPlayer[0];
    currPlayer.erase(currPlayer.begin());
    currPlayer.push_back(first);
}

void Game::movePlayer() {
    if (currPlayer.empty()) return;

    int roll = dice->roll();
    bool doubled = dice->isDouble();
    int doubleCount = 0;
    int total = 0;
    shared_ptr<Player> player = getCurrPlayer();

    player->move(roll); // action is called in move()
    
    while (doubled && doubleCount < 3) {
        ++doubleCount;
        cout << doubleCount << "times rolled Double" << endl;
        
        if (doubleCount == 3) {
            player->changeinTims(true);
            player->moveto(TIMSLINE_POS);
            cout << player->getName() << "rolled three times double. Sent to DC Tims Line" << endl;
            return;
        }

        roll = dice->roll();
        doubled = dice->isDouble();
        player->move(roll); 
    }
    
}

void Game::trade() { // change needed tmr
    string playerName, give, receive;
    cout << "Enter the name of the player to trade with: ";
    cin >> playerName;

    shared_ptr<Player> otherPlayer = findPlayer(playerName);
    if (!otherPlayer) {
        cout << "Player " << playerName << " not found." << endl;
        return;
    }

    cout << "Enter what you want to give: ";
    cin >> give;
    cout << "Enter what you want to receive: ";
    cin >> receive;

    // Perform the trade
    if (getCurrPlayer()->trade(*otherPlayer, give, receive)) {
        cout << "Trade successful between " << getCurrPlayer()->getName()
             << " and " << otherPlayer->getName() << "." << endl;
    } else {
        cout << "Trade failed." << endl;
    }
}

void Game::all() {
    cout << "Display all players' assets" << endl;
    for (auto& player : players) {
        cout << player.getName() << ": " << player.getAssets() << endl;
    }
}

shared_ptr<Player> Game::findPlayer(string name) {
    for (auto &player : currPlayer) {
        if (player->getName() == name) {
            return player;
        }
    }
    return nullptr;
}
