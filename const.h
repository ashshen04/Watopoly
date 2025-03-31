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

std::shared_ptr<Player> string_to_player(const std::string& name, Game& game);
std::shared_ptr<Property> string_to_property(const std::string& name, Game& game);

#endif
