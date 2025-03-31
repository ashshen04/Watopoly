#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <cstring>
#include "game.h"
#include "board.h"
#include "player.h"
#include "property.h"
#include "nonproperty.h"
#include "square.h"
#include "osap.h"
#include "command.h"
#include "utils.h"
#include "const.h"
#include "dice.h"
#include "game.h"
#include "academic.h"
#include "residence.h"
#include "nhall.h"
#include "observer.h"
#include "rolluprimcup.h"
#include "gym.h"
#include "slc.h"
#include "subject.h"
#include "timsline.h"
#include "tuition.h"
#include "utils.h"
#include "coop.h"
#include "gototims.h"
#include "goosenesting.h"
using namespace std;

class Player;

int main(int argc, char* argv[]) {
    std::cout << "Welcome to Watopoly :)" << std::endl;
    const int MIN_PLAYER = 2;
    const int MAX_PLAYER = 8;
    
    // position const int
    const int OSAP_POS = 0;
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
    Command command{game};
    
    vector<shared_ptr<Square>> sq;
    sq.emplace_back(make_shared<OSAP_type>("OSAP", 0));
    sq.emplace_back(make_shared<Academic>("AL", 1, nullptr, 40, 50, std::vector<int>{2, 10, 30, 90, 160, 250}));
    sq.emplace_back(make_shared<SLC>("SLC", 2));
    sq.emplace_back(make_shared<Academic>("ML", 3, nullptr,  60, 50, vector<int>{4, 20, 60, 180, 320, 450}));
    sq.emplace_back(make_shared<Tuition>("Tuition", 4));
    sq.emplace_back(make_shared<Residence>("MKV", 5, nullptr));
    sq.emplace_back(make_shared<Academic>("ECH", 6, nullptr, 100, 50, vector<int>{6, 30, 90, 270, 400, 550}));
    sq.emplace_back(make_shared<NHall>("NeedlesHall", 7));
    sq.emplace_back(make_shared<Academic>("PAS", 8, nullptr,  100, 50, vector<int>{6, 30, 90, 270, 400, 550}));
    sq.emplace_back(make_shared<Academic>("HH", 9, nullptr,  120, 50, vector<int>{8, 40, 100, 300, 450, 600}));
    sq.emplace_back(make_shared<TimsLine>("DCTimsLine", 10));
    sq.emplace_back(make_shared<Academic>("RCH", 11, nullptr, 140, 100, vector<int>{10, 50, 150, 450, 625, 750}));
    sq.emplace_back(make_shared<Gym>("PAC", 12, nullptr));
    sq.emplace_back(make_shared<Academic>("DWE", 13, nullptr, 140, 100, vector<int>{10, 50, 150, 450, 625, 750}));
    sq.emplace_back(make_shared<Academic>("CPH", 14, nullptr, 160, 100, vector<int>{12, 60, 180, 500, 700, 900}));
    sq.emplace_back(make_shared<Residence>("UWP", 15, nullptr));
    sq.emplace_back(make_shared<Academic>("LHI", 16, nullptr,  180, 100, vector<int>{14, 70, 200, 550, 750, 950}));
    sq.emplace_back(make_shared<SLC>("SLC", 17));
    sq.emplace_back(make_shared<Academic>("BMH", 18, nullptr,  180, 100, vector<int>{14, 70, 200, 550, 750, 950}));
    sq.emplace_back(make_shared<Academic>("OPT", 19, nullptr, 200, 100, std::vector<int>{16, 80, 220, 600, 800, 1000}));
    sq.emplace_back(make_shared<GooseNesting>("GooseNesting", 20));
    sq.emplace_back(make_shared<Academic>("EV1", 21, nullptr, 220, 150, std::vector<int>{18, 90, 250, 700, 875, 1050}));
    sq.emplace_back(make_shared<NHall>("NeedlesHall", 22));
    sq.emplace_back(make_shared<Academic>("EV2", 23, nullptr, 220, 150, std::vector<int>{18, 90, 250, 700, 875, 1050}));
    sq.emplace_back(make_shared<Academic>("EV3", 24, nullptr, 240, 150, std::vector<int>{20, 100, 300, 750, 925, 1100}));
    sq.emplace_back(make_shared<Residence>("V1", 25, nullptr));
    sq.emplace_back(make_shared<Academic>("PHYS", 26, nullptr, 260, 150, std::vector<int>{22, 110, 330, 800, 975, 1150}));
    sq.emplace_back(make_shared<Academic>("B1", 27, nullptr, 260, 150, std::vector<int>{22, 110, 330, 800, 975, 1150}));
    sq.emplace_back(make_shared<Gym>("CIF", 28, nullptr));
    sq.emplace_back(make_shared<Academic>("B2", 29, nullptr, 280, 150, std::vector<int>{24, 120, 360, 850, 1025, 1200}));
    sq.emplace_back(make_shared<GotoTims>("GotoTims", 30));
    sq.emplace_back(make_shared<Academic>("EIT", 31, nullptr, 300, 200, std::vector<int>{26, 130, 390, 900, 1100, 1275}));
    sq.emplace_back(make_shared<Academic>("ESC", 32, nullptr, 300, 200, std::vector<int>{26, 130, 390, 900, 1100, 1275}));
    sq.emplace_back(make_shared<SLC>("SLC", 33));
    sq.emplace_back(make_shared<Academic>("C2", 34, nullptr, 320, 200, std::vector<int>{28, 150, 450, 1000, 1200, 1400}));
    sq.emplace_back(make_shared<Residence>("REV", 35, nullptr));
    sq.emplace_back(make_shared<NHall>("NeedlesHall", 36));
    sq.emplace_back(make_shared<Academic>("MC", 37, nullptr, 350, 200, std::vector<int>{35, 175, 500, 1100, 1300, 1500}));
    sq.emplace_back(make_shared<Coop>("Co-opFee", 38));
    sq.emplace_back(make_shared<Academic>("DC", 39, nullptr, 400, 200, std::vector<int>{50, 200, 600, 1400, 1700, 2000}));
    
    game.setSquares(sq);


    vector<shared_ptr<Property>> pro;
    for(auto & square : sq) {
        if (auto property = dynamic_pointer_cast<Property>(square)) {
            pro.emplace_back(property);
        }
    }

    game.setProperties(pro);

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
            }

            // adding properties and improvements to the players
            for (int i = 1; i <= BUILDING_NUM; ++i) {
                string property_name;
                string owner_name;
                int improvements;

                ifs >> property_name >> owner_name >> improvements;

                if (owner_name != "BANK") {
                    for (auto p : game.getPlayers()) {
                        if (p->getName() == owner_name) {
                            game.AddProperty(property_name, owner_name, improvements);
                        }
                    }
                }
            }

            game.StartGame();
            command.readInput(cin, false);
            game.EndGame();

        // Testing Mode (-testing)
        } else if (strcmp(argv[1],"-testing") == 0) {
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

            game.AddPlayer(name, character, 0, DEFAULT_MONEY, OSAP_POS);
        }

        cout << "All players have been added. Starting the game!" << endl;
        game.StartGame();
        command.readInput(cin, true);
        game.EndGame();
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

            game.AddPlayer(name, character, 0, DEFAULT_MONEY, OSAP_POS);
        }

        cout << "All players have been added. Starting the game!" << endl;
        game.StartGame();
        command.readInput(cin, false);
        game.EndGame();
    }
}
