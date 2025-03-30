#ifndef ACADEMIC_H
#define ACADEMIC_H

#include <vector>
#include <string>
#include <memory>
#include "property.h"
#include "player.h"

using namespace std;

class MonopolyBlock; // Forward declaration

class Academic : public Property {
    double purchaseCost;
    double improveCost;
    vector<int> fee;
    int improveNum = 0;
    MonopolyBlock *parentBlock = nullptr; // Pointer to the parent MonopolyBlock

public:
    Academic(const string name, int position, shared_ptr<Player> owner,
        int purchaseCost, int improveCost, const vector<int> &fee);
    void setParentBlock(MonopolyBlock *block) {parentBlock = block;}

    double getFee() override;
    double getPurchaseCost() override;
    void buyImprove() override;
    void sellImprove() override;

    ~Academic() override = default;
};

class MonopolyBlock {
    string monopolyName;
    vector<shared_ptr<Academic>> academics;

public:
    MonopolyBlock(const string &name) : monopolyName(name) {}

    void addAcademic(const shared_ptr<Academic> &academic) {
        academics.push_back(academic);
        academic->setParentBlock(this);
    }

    const vector<shared_ptr<Academic>> &getAcademics() const { return academics; }

    bool isMonopolyOwnedBy(const shared_ptr<Player> &player) const;
};

#endif