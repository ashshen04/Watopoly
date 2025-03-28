#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include "board.h"
#include "game.h"
using namespace std;

class Command {
    Game& game;

    public:
        Command(Game& game);
        void readInput(istream& in);
};

#endif
