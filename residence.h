#ifndef RESIDENCE_H
#define RESIDENCE_H
#include <vector>
#include <string>
#include <memory>
#include "property.h"
#include "player.h"

class Residence : public Property {
    static const int PURCHASE_COST = 200;
public:
    Residence(const string name, int position,shared_ptr<Player> owner):
        Property{name,position,owner}{};
    double getFee() override;
    double getPurchaseCost() override;
    ~Residence() override = default;
};

#endif
