#include <iostream>
#include <fstream>
#include <memory>
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
    : name{name}, character{character}, timsCups{timscup}, money{money}, position{position}, playerImproveCost{0},game(game) {
        assets = money;
    }


// void Player::calculateAssets() {
//     int building_money = 0;
//     for (auto const & building : properties) {
//         building_money += building->getImproveTotal();
//         building_money += building->getPurchaseCost();
//         if (building->isMortgaged()) {
//             building_money -= building->getPurchaseCost() / 2;
//         }
//     }
//     assets = money + building_money;
// }

double Player::getAssets() {
    return assets;
};


void Player::improve(shared_ptr<Property> property) {
    if (property->getOwner()->getName() != name) {
        cout << "You do not own this property." << endl;
        return;
    } if(dynamic_pointer_cast<Academic>(property) == nullptr) {
        assets += property->buyImprove();
        cout << "You have improved " << property->getName()<< endl;
        notifyObservers(property->getPosition(), property->getImproveNum(),0,0,0);
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
        addProperty(receive);
        
        other->AddMoney(give);
        other->removeProperty(receive);
        cout << "Trade successful!" << endl;
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
        removeProperty(give);
        addProperty(receive);
        other->addProperty(give);
        other->removeProperty(receive);
        cout << "Trade successful!" << endl;
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
        removeProperty(give);
        AddMoney(receive);
        other->SubMoney(receive);
        other->addProperty(give);
        cout << "Trade successful!" << endl;
        return true;
    } else {
        cout << "Trade cancelled." << endl;
        return false;
    }
}


void Player::addProperty(shared_ptr<Property> property) {
    properties.push_back(property);
    if (dynamic_pointer_cast<Gym>(property)) {
        GymNums++;
    } else if (dynamic_pointer_cast<Residence>(property)) {
        ResNums--;
    } 
    property->setOwner(shared_from_this());
    assets+=property->getPurchaseCost();
}

void Player::removeProperty(shared_ptr<Property> property) {
    for (auto it = properties.begin(); it != properties.end(); ++it) {
        if (*it == property) {
            if (dynamic_pointer_cast<Gym>(property)) {
                GymNums--;
            } else if (dynamic_pointer_cast<Residence>(property)) {
                ResNums--;
            }
            property->setOwner(nullptr);
            properties.erase(it);
            assets-=property->getPurchaseCost();
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
        while(money < subed) {
            int tmp = subed - money;
            cout<<"Still need "<< tmp <<" to pay off your payable, choice you approach(s/m/t)"<<endl;
            cin >> ans;

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
                            property->sellImprove(1);
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

            
        }

    } else {
        cout << getName() << ": You are bankrupt! ^ ^" << endl;
        bankrupt();
    }
}

double Player::SubMoneyInt(double subed) {
    if (subed <= money) {
        money -= subed;
        return subed;
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
                            property->sellImprove(1);
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
        return subed;
    } else {
        double tmp=bankrupt();
        return tmp;
    }
}

double Player::bankrupt() {
    cout << "You are bankrupt!" << endl;
    double tmp=money;
    for (auto const & property : properties) {
        if(property->isMortgaged()) {
            tmp += property->getPurchaseCost() / 2;
            property->unmortgage();
            property->setOwner(nullptr);
        } else if (property->getImproveNum() > 0) {
            tmp += property->getImproveTotal()/2;
            property->sellImprove(property->getImproveNum());
            property->setOwner(nullptr);
            tmp += property->getPurchaseCost();
        } else {
            tmp += property->getPurchaseCost();
            property->setOwner(nullptr);
        }
    }

    shared_ptr<Player> ptr = shared_from_this();
    game.removePlayer(ptr);
    return tmp;
}


void Player::moveto(int pos) {
    notifyObservers(0, 0, position,pos, this->getChar());
    position = pos;
}


void Player::move(int pos) {
    int tmp = position + pos;
    if (tmp > SQUARE_SIZE) { // ie >40 for basic watopoly
        AddMoney(OSAP);
        cout << "Passed by OSAP!!! $200 is added for you!" << endl;
    }
    int oldPosition = position;
    position = tmp % SQUARE_SIZE;
    notifyObservers(0, 0, oldPosition, position, getChar());
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

