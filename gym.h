#ifndef GYM_H
#define GYM_H

#include <vector>
#include <string>
#include <memory>

#include "property.h"
#include "player.h"
#include "dice.h"

class Gym : public Property {
    constexpr static const double PURCHASE_COST = 150;
    Dice dice;  // Add dice for fee calculation

public:
    Gym(const string name, int position,shared_ptr<Player> owner):
        Property{name,position,owner}{};
    double getFee() override;
    double getPurchaseCost() override;
    ~Gym() override = default;
};
#endif
