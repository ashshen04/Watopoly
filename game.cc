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

class Player;
class Property;

Game::Game() : dice(std::make_unique<Dice>()), board(std::make_unique<Board>()) {}

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
    shared_ptr<Player> ptr = make_shared<Player>(name, character, timscup, money, position, *this);
    players.emplace_back(ptr);
    currPlayer.emplace_back(ptr);
    ptr->attach(board.get());
    
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
    owner_ptr->addProperty(property);

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
    board->drawBoard(cout);
    squares[player->getPosition()]->action(*player);
    
    while (doubled && doubleCount < 3) {
        ++doubleCount;
        cout << doubleCount << " times rolled Double" << endl;
        
        if (doubleCount == 3) {
            tmp = player->getPosition();
            player->changeinTims(true);
            player->moveto(TIMSLINE_POS);
            board->drawBoard(cout);
            cout << player->getName() << " rolled three times double. Sent to DC Tims Line" << endl;
            return;
        }

        cout << "You have rolled DOUBLE. Roll Again!!" << endl;

        string command;
        while(cin >> command) {
            if (command == "roll") {
                roll = dice->roll();
                doubled = dice->isDouble();
                tmp = player->getPosition();
                player->move(roll); 
                board->drawBoard(cout);
                squares[player->getPosition()]->action(*player);
                break;
            } else {
                cout << "Error: Invalid command. Please enter 'roll'!" << endl;
            }
        }
    }
    
}

void Game::movePlayer_test() {
    if (currPlayer.empty()) return;

    int d1, d2;
    cin >> d1 >> d2;

    int roll = dice->testroll(d1, d2);
    bool doubled = dice->isDouble();
    int doubleCount = 0;
    int total = 0;
    shared_ptr<Player> player = getCurrPlayer();

    int tmp = player->getPosition();
    player->move(roll); // action is called in move()
    board->drawBoard(cout);
    squares[player->getPosition()]->action(*player);
    
    while (doubled && doubleCount < 3) {
        ++doubleCount;
        cout << doubleCount << " times rolled Double" << endl;
        
        if (doubleCount == 3) {
            tmp = player->getPosition();
            player->changeinTims(true);
            player->moveto(TIMSLINE_POS);
            board->drawBoard(cout);
            cout << player->getName() << "rolled three times double. Sent to DC Tims Line" << endl;
            return;
        }

        cout << "You have rolled DOUBLE. Roll Again!!" << endl;

        string command;
        cin >> command;
        if (command == "roll") {
            cin >> d1 >> d2;
            roll = dice->testroll(d1,d2);
            doubled = dice->isDouble();
            tmp = player->getPosition();
            player->move(roll); 
            board->drawBoard(cout);
            squares[player->getPosition()]->action(*player);
        } else {
            cout << "Error: Invalid command. Please enter 'roll'!" << endl;
        }
    }
    
}
bool stringToDouble(const std::string& s, double& result) {
    std::istringstream iss(s);
    iss >> result;
    return (iss && (iss >> std::ws).eof());
}


void Game::trade() { 
    string playerName, give, receive;
    cout << "Enter the name of the player to trade with: ";
    cin >> playerName;

    shared_ptr<Player> otherPlayer = findPlayer(playerName);
    if (!otherPlayer) {
        cout << "Error: Player " << playerName << " not found." << endl;
        return;
    }

    cout << "Enter what you want to give: ";
    cin >> give;
    if (give.empty()) {
        cout << "Error: Invalid input for 'give'." << endl;
        return;
    }

    cout << "Enter what you want to receive: ";
    cin >> receive;
    if (receive.empty()) {
        cout << "Error: Invalid input for 'receive'." << endl;
        return;
    }

    double giveValue, receiveValue;
    shared_ptr<Property> giveProperty = nullptr;
    shared_ptr<Property> receiveProperty = nullptr;

    if (stringToDouble(give, giveValue)) {
        if (stringToDouble(receive, receiveValue)) {
            cout << "You cannot trade money for money." << endl;
            return;
        } else {
            receiveProperty = string_to_property(receive, *this);
            if (!receiveProperty) {
                cout << "Error: Property " << receive << " not found." << endl;
                return;
            }
            getCurrPlayer()->trade(otherPlayer, giveValue, receiveProperty);
        }
    } else if (stringToDouble(receive, receiveValue)) {
        giveProperty = string_to_property(give, *this);
        if (!giveProperty) {
            cout << "Error: Property " << give << " not found." << endl;
            return;
        }
        if (giveProperty->getOwner() != getCurrPlayer()) {
            cout << "Error: You do not own the property " << give << "." << endl;
            return;
        }
        getCurrPlayer()->trade(otherPlayer, giveProperty, receiveValue);
    } else {
        giveProperty = string_to_property(give, *this);
        receiveProperty = string_to_property(receive, *this);
        if (!giveProperty || !receiveProperty) {
            cout << "Error: Invalid trade input." << endl;
            return;
        }
        if (giveProperty->getOwner() != getCurrPlayer()) {
            cout << "Error: You do not own the property " << give << "." << endl;
            return;
        }
        getCurrPlayer()->trade(otherPlayer, giveProperty, receiveProperty);
    }
}

void Game::all() {
    cout << "Display all players' assets" << endl;
    for (auto& player : currPlayer) {
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
    if (checkend()) cout << "The winner is " << getCurrPlayer()->getName() << "!! Congrats" << endl;
}

bool Game::checkend() {
    return getPlayers().size() == 1;
}
