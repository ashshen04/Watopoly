#include "property.h"
#include "gym.h"       
#include "residence.h" 
#include "academic.h"  
using namespace std;

// Property constructor implementation
Property::Property(const string name, int position, shared_ptr<Player> owner = nullptr) : 
    Square{name, position},
    improveNum(0), 
    mortgaged(false),
    improveTotal(0),
    owner(owner) {}

shared_ptr<Player> Property::getOwner() {return owner;}
void Property::setOwner(shared_ptr<Player> newOwner) {owner = newOwner;}

void Property::action(Player& p) {
    if (owner == nullptr) {
        double price = getPurchaseCost();
        cout << name<<" is available for purchase at "<< price << endl;
        if (p.getAssets() < price) {
            cout << "You do not have enough money to buy this property." << endl;
            //auction();
            return;
        } else {
            cout << "You have " << p.getMoney() << "cash and "<<p.getAssets() <<". Would you like to buy it? (y)" << endl;
            char choice;
            cin >> choice;
            if (choice == 'y') {
                p.SubMoney(price);
                setOwner(make_shared<Player>(p));
                p.addProperty(this);
                cout << "Congraulation! You have brought "<<name << endl;
                if (dynamic_cast<Gym*>(this)) {
                    p.GymNums++;
                } else if (dynamic_cast<Residence*>(this)) {
                    p.ResNums++;
                } 
                return;
            } else {
                cout << "You chose not to buy this property. Entering auction." << endl;
                //auction();
            }
        } 
    } else if (owner->getName() != p.getName()) {
        cout << "You must pay rent to the owner of this property." << endl;
        double money = p.SubMoneyInt(getFee());
        owner->AddMoney(money);
        cout << "You paid " << money << " to " << owner->getName() << endl;
    } else {
        cout << "You own this property." << endl;
    }
}

void Property::mortgage() {
    if (mortgaged) {
        cout << "Property is already mortgaged." << endl;
        return;
    }
    if (improveNum > 0) {
        cout << "Cannot mortgage property with improvements." << endl;
        return;
    }
    mortgaged = true;
    owner->AddMoney(getPurchaseCost() / 2);
    improveNum = -1; 
    cout << "Property " << name << " has been mortgaged." << endl;
}

void Property::unmortgage() {
    double payable = getPurchaseCost() *0.6;
    if (!mortgaged) {
        cout << "Property is not mortgaged." << endl;
        return;
    }
    if (owner->getAssets() < payable) {
        cout << "Not enough money to unmortgage." << endl;
        return;
    }
    owner->SubMoney(payable);
    mortgaged = false;
    improveNum = 0; 
    cout << "Property " << name << " has been unmortgaged." << endl;
}







