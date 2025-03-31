#include "academic.h"
#include "player.h"
using namespace std;


Academic::Academic(const string name, int position, shared_ptr<Player> owner, 
                    int purchaseCost, int improveCost, const vector<int> &fee) :
    Property{name, position,owner},
    purchaseCost(purchaseCost),
    improveCost(improveCost),
    fee(fee) {}


bool MonopolyBlock::isMonopolyOwnedBy(const shared_ptr<Player> &player) const {
    for (const auto &academic : academics) {
        if (academic->getOwner() != player) {
            return false;
        }
    }
    return true;
}

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
    return purchaseCost;
}

double Academic::buyImprove() {
    if (isMortgaged()) {
        cout << "You cannot improve " << getName() << " as it's mortgaged" << endl;
        return 0;
    }
    if (improveNum >= 5) {
        cout << "You cannot improve " << getName() << " as it is already at max level" << endl;
        return 0;
    }
    if (getOwner()->getMoney() < improveCost) {
        cout << "You do not have enough money to improve " << getName() << endl;
        return 0;
    }
    getOwner()->SubMoney(improveCost);
    getOwner()->playerImproveCost += improveCost;
    improveNum++;
    improveTotal += improveCost;

    cout << "You have improved " << getName() << " to level " << improveNum << endl;
    return improveCost;
}

void Academic::sellImprove(int i) {
    if (isMortgaged()) {
        cout << "You cannot sell improvement on " << getName() << " as it's mortgaged" << endl;
        return;
    }
    if (improveNum == 0) {
        cout << "You cannot sell improvement on " << getName() << " as it is already at level 0" << endl;
        return;
    }
    double moneyEarned = improveCost*i / 2;
    getOwner()->AddMoney(moneyEarned);
    cout << "You have sold improvement on " << name << " for " << moneyEarned << endl;
    improveNum-= i;
    improveTotal -= improveCost*i;
    getOwner()->playerImproveCost -= improveCost*2; 

    cout << name << " is now level " << improveNum << endl;

}
