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
    string command;

    while (in >> command) {
        if (command == "roll") {
            game.movePlayer();
        } else if (command == "next") {
            game.nextPlayer();
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
            shared_ptr<Property> property_to_apply = string_to_property(property_name, game);
            // not finished yet, return back to this after class of Mortage is implemented
        } else if (command == "unmortgage") {
            string property_name;
            in >> property_name;
            // same for this
        } else if (command == "bankrupt") {
            game.getCurrPlayer()->bankrupt(); // Access currPlayer through a public getter method
        } else if (command == "assets") {
            if (game.getCurrPlayer()->getPosition() != TUITION_POS) {
                game.getCurrPlayer()->calculateAssets();
                cout << "You have" << game.getCurrPlayer()->getAssets() << "assets." << endl;
            } else {
                cerr << "Error: cannot open assets in Tuition!!! Make decision on your own" << endl;
            }
        } else if (command == "all") {
            game.all();
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
        } else if (command == "exit") {
            break;
        } else {
            cerr << "Error: Invalid input. Re-enter" << endl;
        }
    }
}






