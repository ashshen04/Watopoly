#include "const.h"
using namespace std;

shared_ptr<Property> string_to_property(string &name, Game& game) {
    for (auto &property : game.getProperties()) {
        if (property->getName() == name) {
            return property;
        }
    }
    return nullptr;
}


shared_ptr<Player> string_to_player(string &name, Game& game) {
    for (auto& player : game.getPlayers()) {
        if (player->getName() == name) {
            return player;
        }
    }
    return nullptr;
}
