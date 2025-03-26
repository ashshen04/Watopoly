#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "game.h"
using namespace std;

class Player;

int main(int argc, char* argv[]) {
    cout << "Welcome to Watopoly :)" << endl;
    const int MIN_PLAYER = 2;
    const int MAX_PLAYER = 8;

    int player_num;
    Game game;

    
    // Loading previous game (-load file)
    if (argv[1] == "-load" && argc == 3) {
        string game_file;
        game_file = argv[2];
        ifstream ifs{game_file};

        cout << "Loading Previous Saved Game in" << game_file << endl;

        // start to read through input file
        ifs >> player_num;
        
        // adding all players
        for (int i = 1; i <= player_num; ++i) {
            string name;
            char character;
            int timscups;
            int money;
            int pos;

            ifs >> name;
            ifs >> character;
            ifs >> timscups;
            ifs >> money;
            ifs >> pos;

            Player player = {name, character, timscups, money, pos};
            game.AddPlayer(player);
        }

        // moving all players to the correct position

        // adding properties and improvements to the players
    }

    // New game is created

    // Testing Mode (-testing)

}
