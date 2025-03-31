#ifndef PROPERTY_H
#define PROPERTY_H

#include "square.h" 
#include "player.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>
using namespace std;

class Player;

class Property : public Square, public enable_shared_from_this<Property>  {
    protected:
        int improveNum; //improveNum=-1 if it is mortaged
        double improveTotal;
        bool mortgaged;
        shared_ptr<Player> owner;

    public:
        Property(const string name, int position, shared_ptr<Player> owner);
        virtual ~Property() = default;
        
        int getImproveNum() { return improveNum; };
        bool isMortgaged() const { return mortgaged; };
        double getImproveTotal() { return improveTotal; };


        shared_ptr<Player> getOwner();

        void setOwner(shared_ptr<Player> owner);
        void auction();
        void action(Player&p);
        void mortgage();
        void unmortgage();

        virtual double getFee()=0;
        virtual double getPurchaseCost()=0;

        virtual void buyImprove() {
            throw std::logic_error("Improvements are not supported for this property.");
        }
        virtual void sellImprove(int num) {
            throw std::logic_error("Improvements are not supported for this property.");
        }
};

#endif