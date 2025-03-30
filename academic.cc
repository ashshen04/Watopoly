#include "academic.h"
#include "player.h"
using namespace std;


Academic::Academic(const string name, int position, shared_ptr<Player> owner, 
                    int purchaseCost, int improveCost, const vector<int> &fee) :
    Property{name, position,owner},
    purchaseCost(purchaseCost),
    improveCost(improveCost),
    fee(fee) {}

// Check if a single player owns all academics in the MonopolyBlock
bool MonopolyBlock::isMonopolyOwnedBy(const shared_ptr<Player> &player) const {
    for (const auto &academic : academics) {
        if (academic->getOwner() != player) {
            return false; // If any academic is not owned by the player, return false
        }
    }
    return true; // All academics are owned by the player
}

// Get the fee for the Academic property
double Academic::getFee() {
    if (isMortgaged()) {
        cout << name << " is mortgaged, you don't need to pay" << endl;
        return 0;
    }
    if (!getOwner()) {
        cout << name << " is not owned by anyone, you don't need to pay" << endl;
        return 0;
    }
    if (improveNum == 0 && parentBlock && parentBlock->isMonopolyOwnedBy(getOwner())) {
        cout << "You have to pay double fee "<< fee[0] * 2 <<" as the owner own all the academics in the block" << endl;
        return fee[0] * 2;
    }
    int payable=fee[improveNum];
    cout << "You have to pay " << payable <<" as the building was improved "<<improveNum<< " times." << endl;
    return payable;
}

double Academic::getPurchaseCost() {
    cout<<"Price for academic" << name<<" is: "<<purchaseCost << endl;
    return purchaseCost;
}

void Academic::buyImprove() {
    if (isMortgaged()) {
        cout << "You cannot improve " << getName() << " as it's mortgaged" << endl;
        return;
    }
    if (improveNum >= 5) {
        cout << "You cannot improve " << getName() << " as it is already at max level" << endl;
        return;
    }
    if (getOwner()->getMoney() < improveCost) {
        cout << "You do not have enough money to improve " << getName() << endl;
        return;
    }
    getOwner()->SubMoney(improveCost);
    getOwner()->playerImproveCost += improveCost;
    improveNum++;
    improveTotal += improveCost;

    cout << "You have improved " << getName() << " to level " << improveNum << endl;
}

void Academic::sellImprove() {
    if (isMortgaged()) {
        cout << "You cannot sell improvement on " << getName() << " as it's mortgaged" << endl;
        return;
    }
    if (improveNum == 0) {
        cout << "You cannot sell improvement on " << getName() << " as it is already at level 0" << endl;
        return;
    }
    double moneyEarned = improveCost / 2;
    getOwner()->AddMoney(moneyEarned);
    cout << "You have sold improvement on " << name << " for " << moneyEarned << endl;
    improveNum--;
    improveTotal -= improveCost;
    getOwner()->playerImproveCost -= improveCost; 

    cout << name << " is now level " << improveNum << endl;

}
