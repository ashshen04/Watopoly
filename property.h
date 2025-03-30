#ifndef PROPERTY_H
#define PROPERTY_H
#include "square.h"
#include "player.h"
using namespace std;

#include <vector>
#include <string>
#include <memory>
#include <iostream>


class Property:public Square{
    protected:
        string name;
        int improveNum; //improveNum=-1 if it is mortaged
        bool mortgaged;
        shared_ptr<Player> owner;
        int position;
    public:
        Property(const string name, int position);
        virtual ~Property() = default;
        
        string getName() const { return name; }
        int getPosition() const { return position; }
        int getImproveNum() { return improveNum; }
        bool isMortgaged() const { return mortgaged; }
        shared_ptr<Player> getOwner();
        
        void setOwner(shared_ptr<Player> owner);
        void auction();
        void action(Player&p);
        void mortgage();
        void unmortgage();

        virtual int getFee()=0;
        virtual int getPurchaseCost()=0;

        virtual void buyImprove() {
            throw std::logic_error("Improvements are not supported for this property.");
        }
        virtual void sellImprove() {
            throw std::logic_error("Improvements are not supported for this property.");
        }
};

#endif