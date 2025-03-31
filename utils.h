#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <memory>
#include "property.h"
#include "game.h"
#include "player.h"

std::shared_ptr<Property> string_to_property(const std::string& name, Game& game);
std::shared_ptr<Player> string_to_player(const std::string& name, Game& game);

#endif 

