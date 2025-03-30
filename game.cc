#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
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
    // board adding players
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

    int tmp = player->getPosition();
    player->move(roll); // action is called in move()
    board->updatePlayer(tmp, tmp+roll, player->getChar());
    board->drawBoard(cout);
    
    while (doubled && doubleCount < 3) {
        ++doubleCount;
        cout << doubleCount << "times rolled Double" << endl;
        
        if (doubleCount == 3) {
            tmp = player->getPosition();
            player->changeinTims(true);
            player->moveto(TIMSLINE_POS);
            board->updatePlayer(tmp, TIMSLINE_POS, player->getChar());
            board->drawBoard(cout);
            cout << player->getName() << "rolled three times double. Sent to DC Tims Line" << endl;
            return;
        }

        roll = dice->roll();
        doubled = dice->isDouble();
        tmp = player->getPosition();
        player->move(roll); 
        board->updatePlayer(tmp, tmp+roll, player->getChar());
        board->drawBoard(cout);
    }
    
}

void Game::trade() { 
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

    double giveValue, receiveValue;
    bool giveIsDouble = false, receiveIsDouble = false;
    stringstream sgive(give), srece(receive);
    if (sgive >> giveValue && sgive.eof()) {
        giveIsDouble = true;
    }
    if (srece >> receiveValue && srece.eof()) {
        receiveIsDouble = true;
    }

    if(giveIsDouble && receiveIsDouble) {
        cout << "Trade money for money is not allowed." << endl;
        return;
    } else if(giveIsDouble) {
        shared_ptr<Property> receiveProperty = string_to_property(receive, *this);
        getCurrPlayer()->trade(otherPlayer, giveValue, receiveProperty); // money for property
    } else if(receiveIsDouble) {
        shared_ptr<Property> giveProperty = string_to_property(give, *this);
        getCurrPlayer()->trade(otherPlayer, giveProperty, receiveValue); // property for money
    } else if(!giveIsDouble && !receiveIsDouble) {
        shared_ptr<Property> giveProperty = string_to_property(give, *this);
        shared_ptr<Property> receiveProperty = string_to_property(receive, *this);
        if (giveProperty && receiveProperty) {
            getCurrPlayer()->trade(otherPlayer, giveProperty, receiveProperty); // property for property
        } else {
            cout << "Invalid trade." << endl;
            return;
        }
    }
    cout << "Trade successful between " << getCurrPlayer()->getName()
             << " and " << otherPlayer->getName() << "." << endl;
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
