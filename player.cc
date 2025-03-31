#include <iostream>
#include <fstream>
#include <string>
#include "player.h"
#include "property.h"
#include "academic.h"
#include "gym.h"       
#include "residence.h" 
#include "const.h"
#include "game.h"

using namespace std;

Player::Player(string name, char character, int timscup, double money, int position, Game &game) 
    : name{name}, character{character}, timsCups{timscup}, money{money}, position{position}, playerImproveCost{0},game(game) {}


void Player::calculateAssets() {
    int building_money = 0;
    for (auto const & building : properties) {
        building_money += building->getImproveTotal();
        building_money += building->getPurchaseCost();
        if (building->isMortgaged()) {
            building_money -= building->getPurchaseCost() / 2;
        }
    }
    assets = money + building_money;
}


void Player::improve(shared_ptr<Property> property) {
    if (property->getOwner()->getName() != name) {
        cout << "You do not own this property." << endl;
        return;
    } if(dynamic_cast<Academic*>(property.get()) == nullptr) {
        property->buyImprove();
        cout << "You have improved " << property->getName()<< endl;
        calculateAssets();
        notifyObservers(property->getPosition(), property->getImproveNum());
    } else {
        cout << "You cannot improve this property." << endl;
    }
    return;
}

bool Player::trade(shared_ptr<Player> other, int give, shared_ptr<Property> receive) {
    cout<< name <<" trading " << give << " for " << other->getName() <<"'s "<< receive->getName() << endl;
    cout<< other->getName() <<" has " << other->getMoney() << " and " << other->getAssets() << " in assets." ; 
    cout<<"Do you want to trade? (y)" << endl;
    char ans;
    cin >> ans;
    if (ans == 'y') {
        SubMoney(give);
        addProperty(receive.get());
        other->AddMoney(give);
        other->removeProperty(receive.get());
        cout << "Trade successful!" << endl;
        calculateAssets();
        other->calculateAssets();
        return true;
    } else {
        cout << "Trade cancelled." << endl;
        return false;
    }
    
}

bool Player::trade(shared_ptr<Player> other, shared_ptr<Property> give, shared_ptr<Property> receive) {
    cout<< name <<" trading " << give->getName() << " for " << other->getName() <<"'s "<< receive->getName() << endl;
    cout<< other->getName() <<" has " << other->getMoney() << " and " << other->getAssets() << " in assets." ; 
    cout<<"Do you want to trade? (y)" << endl;
    char ans;
    cin >> ans;
    if (ans == 'y') {
        removeProperty(give.get());
        addProperty(receive.get());
        other->addProperty(give.get());
        other->removeProperty(receive.get());
        cout << "Trade successful!" << endl;
        calculateAssets();
        other->calculateAssets();
        return true;
    } else {
        cout << "Trade cancelled." << endl;
        return false;
    }
}

bool Player::trade(shared_ptr<Player> other, shared_ptr<Property> give, int receive) {
    cout<< name <<" trading " << give->getName() << " for " << other->getName() <<"'s "<< receive << endl;
    cout<< other->getName() <<" has " << other->getMoney() << " and " << other->getAssets() << " in assets." ; 
    cout<<"Do you want to trade? (y)" << endl;
    char ans;
    cin >> ans;
    if (ans == 'y') {
        removeProperty(give.get());
        AddMoney(receive);
        other->SubMoney(receive);
        other->addProperty(give.get());
        cout << "Trade successful!" << endl;
        calculateAssets();
        other->calculateAssets();
        return true;
    } else {
        cout << "Trade cancelled." << endl;
        return false;
    }
}


void Player::addProperty(Property *property) {
    properties.push_back(shared_ptr<Property>(property));
    if (dynamic_cast<Gym*>(property)) {
        GymNums++;
    } else if (dynamic_cast<Residence*>(property)) {
        ResNums--;
    } 
    calculateAssets();
}
void Player::removeProperty(Property *property) {
    for (auto it = properties.begin(); it != properties.end(); ++it) {
        if (it->get() == property) {
            properties.erase(it);
            if (dynamic_cast<Gym*>(it->get())) {
                GymNums--;
            } else if (dynamic_cast<Residence*>(it->get())) {
                ResNums--;
            } 
            calculateAssets();
            return;
        }
    }
    cout << "Property not found." << endl;
}

void Player::AddMoney(double added) {money += added;}
void Player::SubMoney(double subed) {
    if (subed <= money) {
        money -= subed;
        return;
    } else if (subed <= assets) {
        cout<< "You do not have enough money, but you can use your assets to pay." << endl;
        cout<< "You can either sale improvement(s), get mortgaged your properties(m), or trade with others(t)" << endl;
        char ans;
        cin >> ans;
        while(money < subed) {
            if (ans == 's'){
                if (playerImproveCost>0){
                    cout<< "Sell improvement(s) on your properties:" << endl;
                    for (auto const & property : properties) {
                        if (property->getImproveNum() > 0) {
                            cout << property->getName() << " has been improved with a total of " << property->getImproveTotal() << " $" << endl;
                        }
                    }
                    cout<< "Which property do you want to sell improvement(s) on?" << endl;
                    string name;
                    cin >> name;
                    for (auto const & property : properties) {
                        if (property->getName() == name) {
                            property->sellImprove();
                            break;
                        }
                    }
                } else {cout<< "You do not have any improvement(s) to sell." << endl;}
            } else if (ans == 'm') {
                cout<< "Mortgage your properties:" << endl;
                for (auto const & property : properties) {
                    if (!property->isMortgaged()) {
                        cout << property->getName() << " is not mortgaged." << endl;
                    }
                }
                cout<< "Which property do you want to mortgage?" << endl;
                string name;
                cin >> name;
                for (auto const & property : properties) {
                    if (property->getName() == name) {
                        property->mortgage();
                        break;
                    }
                }
            } else if (ans == 't') {
                cout<< "Initiating trade..." << endl;
                game.trade();
                // need inpleementation
            } else {
                cout<< "Invalid input, please try again." << endl;
            }

            int tmp = subed - money;
            cout<<"Still need "<< tmp <<" to pay off your payable, choice you approach(s/m/t)"<<endl;
            cin >> ans;
        }

    } else {
        cout << "You are bankrupt! ^ ^" << endl;
        bankrupt();
    }
}

void Player::moveto(int pos) {
    position = pos;
}


void Player::move(int pos) {
    int tmp = position + pos;
    if (tmp > SQUARE_SIZE) { // ie >40 for basic watopoly
        AddMoney(OSAP);
        cout << "Passed by OSAP!!! $200 is added for you!" << endl;
    }
    position = tmp % SQUARE_SIZE;
    notifyObservers(position, 0);
}

void Player::outofTims() {
    changeinTims(false);
    timsTurn = 0;
}

int Player::AddTimsTurn() {
    ++timsTurn; 
    return timsTurn;
}

Player::~Player() {}

