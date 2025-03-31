#include "utils.h"
#include "academic.h"
#include "gym.h"
#include "residence.h"

std::shared_ptr<Property> string_to_property(const std::string& name, Game& game) {
    // Get all properties from the game
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
    // Get all players from the game
    auto players = game.getPlayers();
    
    // Search for a player with matching name
    for (auto& player : players) {
        if (player->getName() == name) {
            return player;
        }
    }
    
    return nullptr;
} 