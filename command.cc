#include "command.h"
#include "utils.h"
#include "board.h"
#include "game.h"
#include "const.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Command::Command(Game& game): game{game} {}

void Command::readInput(istream &in){
    bool rolled = false;
    string command;

    cout << "It is " << game.getCurrPlayer()->getName() << "'s Turn!" << endl;
    while (in >> command) {
        if (command == "roll") {
            if (rolled == false) {
                game.movePlayer();
                rolled = true;
            } else {
                cerr << "You have rolled before. Make other actions or pass to next player!" << endl;
            }  
        } else if (command == "next") {
            game.nextPlayer();
            cout << "It is " << game.getCurrPlayer()->getName() << "'s Turn!" << endl;
            rolled = false;
        } else if (command == "trade") {
            game.trade(); 
        } else if (command == "improve") {
            string property;
            string buy_or_sell;
            if (in >> property >> buy_or_sell) {
                game.getCurrPlayer()->improve(string_to_property(property, game));
            } else {
                cerr << "Error: cannot improved because of invalid input" << endl;
            }
        } else if (command == "mortage") {
            string property_name;
            in >> property_name;
            shared_ptr<Property> property = string_to_property(property_name, game);
            if (property) {
                if(property->getOwner() == game.getCurrPlayer()) {
                    property->mortgage();
                } else {
                    cerr << "Error: You do not own this property" << endl;
                }
            } else {
                cerr << "Error: Property not found" << endl;
            }
        } else if (command == "unmortgage") {
            string property_name;
            in >> property_name;
            shared_ptr<Property> property = string_to_property(property_name, game);
            if (property) {
                if(property->getOwner() == game.getCurrPlayer()) {
                    property->unmortgage();
                } else {
                    cerr << "Error: You do not own this property" << endl;
                }
             } 
        } else if (command == "bankrupt") {
            game.getCurrPlayer()->bankrupt(); // Access currPlayer through a public getter method
        } else if (command == "assets") {
            if (game.getCurrPlayer()->getPosition() != TUITION_POS) {
                game.getCurrPlayer()->calculateAssets();
                cout << "You have $" << game.getCurrPlayer()->getAssets() << " assets." << endl;
            } else {
                cerr << "Error: cannot open assets in Tuition!!! Make decision on your own" << endl;
            }
        } else if (command == "all") {
            if (game.getCurrPlayer()->getPosition() == TUITION_POS) {
                cerr <<  "Error: cannot open assets in Tuition!!! Make decision on your own" << endl;
            } else {
                game.all();
            }
        } else if (command == "save"){
            cout << "Please enter the file that you would like to save this game: " << endl;
            string file_name;
            in >> file_name;
            ofstream save_file{file_name};
            if (save_file) {
                game.SaveGame(save_file);
            } else {
                cerr << "Error: Could not open file " << file_name << " for saving" << endl;
            }
        } else if (command == "q") {
            break;
        } else {
            cerr << "Error: Invalid input. Re-enter" << endl;
        }
    }
}






