#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "game.h"
#include "board.h"
#include "player.h"
#include "property.h"
#include "nonproperty.h"
#include "square.h"
using namespace std;

class Player;

int main(int argc, char* argv[]) {
    std::cout << "Welcome to Watopoly :)" << std::endl;
    const int MIN_PLAYER = 2;
    const int MAX_PLAYER = 8;
    
    // position const int
    const int OSAP = 0;
    const int DC_TIMS_LINE = 10;
    const int GO_TO_TIMS = 30;

    // other setting const int
    const int MAX_num_in_tims = 2;
    const int MIN_IMPROVEMENT = 0;
    const int MAX_IMPROVEMENT = 5;
    const int MORTAGE_IMPROVEMENT = -1; // building only
    const int MAX_TIMS_CUP_ALLOWED = 4;
    const int BUILDING_NUM = 22 + 4 + 2;
    const int DEFAULT_MONEY = 1500;

    int player_num;
    Game game;
    
    // Check if there are enough arguments before accessing argv[1]
    if (argc > 1) {
        // Loading previous game (-load file)
        if (strcmp(argv[1], "-load") == 0 && argc == 3) {
            string game_file;
            game_file = argv[2];
            ifstream ifs{game_file};

            if (!ifs) {
                cout << "Error: Could not open file " << game_file << endl;
                return 1;
            } 

            cout << "Loading Previous Saved Game from " << game_file << endl;

            // start to read through input file
            ifs >> player_num;
            
            // adding and moving all players
            for (int i = 1; i <= player_num; ++i) {
                string name;
                char character;
                int timscups;
                double money;
                int pos;
                int num_in_tims = 0;

                ifs >> name >> character >> timscups >> money >> pos;

                game.AddPlayer(name,character, timscups, money, pos);

                if (pos == 10) {
                    ifs >> num_in_tims;
                    if (num_in_tims > MAX_num_in_tims) {
                        std::cout << "Error: Invalid input in the saved file :(" << std::endl;
                        return 1;
                    }
                }
                game.movePlayer();
            }

            // adding properties and improvements to the players
            for (int i = 1; i <= BUILDING_NUM; ++i) {
                string property_name;
                string owner_name;
                int improvments;

                ifs >> property_name >> owner_name >> improvments;

                if (owner_name != "BANK") {
                    for (auto p : game.getPlayers()) {
                        if (p->getName() == owner_name) {}
                        // game.AddProperty(property_name, owner_name, improvements);
                    }
                }
            }

            // game.LoadGame();

        // Testing Mode (-testing)
        } else if (strcmp(argv[1],"-testing") == 0) {
            // Implement testing mode logic here
        }
    }

    // New game is created
    else {
        cout << "New Game is Created!" << endl;
        cout << "Start Inputting Player Information:" << endl;
        cout << "Enter the number of players (between " << MIN_PLAYER << " and " << MAX_PLAYER << "): ";
        cin >> player_num;

        // deal with invalid input
        while (player_num < MIN_PLAYER || player_num > MAX_PLAYER) {
            cout << "Invalid number of players. Please enter a number between " << MIN_PLAYER << " and " << MAX_PLAYER << ": ";
            cin >> player_num;
        }

        // valid inputs, now add players
        for (int i = 1; i <= player_num; ++i) {
            string name;
            char character;
            cout << "Enter name for Player " << i << ": ";
            cin >> name;
            cout << "Enter a single character to represent Player " << i << ": ";
            cin >> character;

            game.AddPlayer(name, character, 0, DEFAULT_MONEY, OSAP);
        }

        cout << "All players have been added. Starting the game!" << endl;
        game.StartGame();
    }
}