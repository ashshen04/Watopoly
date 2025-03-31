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
#include "utils.h"
#include "academic.h"
#include "gym.h"
#include "residence.h"
using namespace std;

Game::Game() {
    dice = new Dice();
    board = new Board();
}

Game::~Game() {
    delete dice;
    delete board;
}


vector<shared_ptr<Player>> Game::getPlayers() {
    return players;
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

void Game::AddPlayer(string name, char character, int timscup, double money, int position) {
    players.emplace_back(make_shared<Player>(name, character, timscup, money, position, *this));
    currPlayer.emplace_back(make_shared<Player>(name, character, timscup, money, position, *this));
}

void Game::AddProperty(string property_name, string owner, int improvements) {
    shared_ptr<Property> property = string_to_property(property_name, *this);
    if (!property) {
        cout << "Error: Property " << property_name << " not found." << endl;
        return;
    }

    shared_ptr<Player> owner_ptr = string_to_player(owner, *this);
    if (!owner_ptr) {
        cout << "Error: Player " << owner << " not found." << endl;
        return;
    }

    property->setOwner(owner_ptr);
    owner_ptr->addProperty(property.get());

    if (improvements > 0) {
        for (int i = 0; i < improvements; ++i) {
            property->buyImprove();
        }
    }

    cout << "Property " << property_name << " assigned to " << owner << " with " << improvements << " improvements." << endl;
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
        file << player->getName() << " " << player->getChar() << " " 
             << player->getMoney() << " " << player->getPosition() << endl;
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
    board->updatePlayer(tmp, player->getPosition(), player->getChar());
    board->drawBoard(cout);
    squares[player->getPosition()]->action(*player);
    
    while (doubled && doubleCount < 3) {
        ++doubleCount;
        cout << doubleCount << " times rolled Double" << endl;
        
        if (doubleCount == 3) {
            tmp = player->getPosition();
            player->changeinTims(true);
            player->moveto(TIMSLINE_POS);
            board->updatePlayer(tmp, TIMSLINE_POS, player->getChar());
            board->drawBoard(cout);
            cout << player->getName() << "rolled three times double. Sent to DC Tims Line" << endl;
            return;
        }

        cout << "You have rolled DOUBLE. Roll Again!!" << endl;

        string command;
        cin >> command;
        if (command == "roll") {
            roll = dice->roll();
            doubled = dice->isDouble();
            tmp = player->getPosition();
            player->move(roll); 
            board->updatePlayer(tmp, tmp+roll, player->getChar());
            board->drawBoard(cout);
        } else {
            cout << "Error: Invalid command. Please enter 'roll'!" << endl;
        }
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
    shared_ptr<Property> giveProperty = nullptr;
    shared_ptr<Property> receiveProperty = nullptr;

    stringstream sgive(give), srece(receive);
    if (sgive >> giveValue && sgive.eof()) {
        giveProperty = string_to_property(give, *this);
        if(giveProperty && (giveProperty->isMortgaged()|| giveProperty->getImproveNum()!=0)) {
            cout << "You cannot trade a mortgaged property or a property with improvements." << endl;
            return;
        }
    }
    if (srece >> receiveValue && srece.eof()) {
        receiveProperty = string_to_property(receive, *this);
        if(receiveProperty && (receiveProperty->isMortgaged()|| receiveProperty->getImproveNum()!=0)) {
            cout << "You cannot trade a mortgaged property or a property with improvements." << endl;
            return;
        }
    }

    if(giveProperty && receiveProperty){
        getCurrPlayer()->trade(otherPlayer, giveProperty, receiveProperty);
    } else if(giveProperty) {
        getCurrPlayer()->trade(otherPlayer, giveProperty, receiveValue);
    } else if(receiveProperty) {
        getCurrPlayer()->trade(otherPlayer, giveValue, receiveProperty);
    } else {
        cout << "Invalid trade input. You can't trade money for money" << endl;
    }
    
}

void Game::all() {
    cout << "Display all players' assets" << endl;
    for (auto& player : players) {
        player->calculateAssets();
        cout << player->getName() << ": " << player->getAssets() << endl;
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

void Game::removePlayer(shared_ptr<Player> player) {
    vector<shared_ptr<Player>> tempCurr;
    for (auto &p : currPlayer) {
        if (p != player) {
            tempCurr.push_back(p);
        } else {
            p = nullptr;
        }
    }
    currPlayer = tempCurr;

    vector<shared_ptr<Player>> tempPlayers;
    for (auto &p : players) {
        if (p->getName() != player->getName()) {
            tempPlayers.push_back(p);
        } else {
            p = nullptr;
        }
    }
    players = tempPlayers;
}