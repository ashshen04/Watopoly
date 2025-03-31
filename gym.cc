#include "gym.h"
#include "player.h"
#include <iostream>
using namespace std;


double Gym::getPurchaseCost() {
    cout<<"Price for gym" << name<<" is: "<<PURCHASE_COST << endl;
    return PURCHASE_COST;
}

double Gym::getFee() {
    if (!owner) return 0;  // No owner = no fee
    if (isMortgaged()) {
        cout << "Property is mortgaged. No fee." << endl;
        return 0;  
    }
    
    int diceSum = dice.roll();
    int gymsOwned = owner->GymNums; 
    double payable = (gymsOwned == 1) ? diceSum * 4 : diceSum * 10;
    cout<<"Fee for " << name<<" is: "<< payable << endl;
    return payable;
}


