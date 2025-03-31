#ifndef CONST_H
#define CONST_H

#include <memory>
#include <string>
#include "property.h"
#include "player.h"
#include "game.h"

const int MaxCup = 4;
const int TIMSLINE_POS = 10;
const int OSAP_POS = 0;
const int TUITION_POS = 4;

shared_ptr<Property> string_to_property(string name, Game& game) {
    for (auto &property : game.getProperties()) {
        if (property->getName() == name) {
            return property;
        }
    }
    return nullptr;
}


shared_ptr<Player> string_to_player(string name, Game& game) {
    for (auto& player : game.getPlayers()) {
        if (player.getName() == name) {
            return make_shared<Player>(player);
        }
    }
    return nullptr;
}

#endif