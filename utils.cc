#include "utils.h"
#include "academic.h"
#include "gym.h"
#include "residence.h"

std::shared_ptr<Property> string_to_property(const std::string& name, Game& game) {
    auto properties = game.getProperties();
    
    // Search for a property with matching name
    for (auto& property : properties) {
        if (property->getName() == name) {
            return property;
        }
    }
    
    return nullptr;
}

std::shared_ptr<Player> string_to_player(const std::string& name, Game& game) {
    auto players = game.getPlayers();
    
    for (auto& player : players) {
        if (player->getName() == name) {
            return player;
        }
    }
    
    return nullptr;
} 

