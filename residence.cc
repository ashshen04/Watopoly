#include "residence.h"
#include <iostream>
using namespace std;


double Residence::getPurchaseCost() {
    return PURCHASE_COST;
}

double Residence::getFee() {
    if (!getOwner()) return 0;
    if (isMortgaged()){
        cout << "Property is mortgaged. No fee." << endl;
        return 0;  // No fee if property is mortgaged
    }
    int residencesOwned = getOwner()->ResNums;
    int payable = 25 * pow(2, residencesOwned) ;
    cout<<"Fee for " << name<<" is: "<< payable <<" as the owner owns "<<residencesOwned<<" residence."<< endl;
    return payable;
}
