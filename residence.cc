#include "residence.h"
#include <iostream>
using namespace std;


double Residence::getPurchaseCost() {
    cout<<"Price for residence " << name<<" is: "<<PURCHASE_COST << endl;
    return PURCHASE_COST;
}

double Residence::getFee() {
    if (!getOwner()) return 0;
    if (isMortgaged()){
        cout << "Property is mortgaged. No fee." << endl;
        return 0;  // No fee if property is mortgaged
    }
    int residencesOwned = getOwner()->ResNums;
    double payable = 0;
    switch(residencesOwned) {
        case 1: payable = 25;
        case 2: payable = 50;
        case 3: payable = 100;
        case 4: payable = 200;
        default: payable = 0; // Error case
    }
    cout<<"Fee for " << name<<" is: "<< payable << endl;
    return payable;
}