#include "command.h"
#include "board.h"
#include "game.h"
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
            // this turn do something here
        } else if (command == "next") {
            game.nextPlayer();
        } else if (command == "trade") {
            game.trade();
        } else if (command == "improve") {
            string property;
            string buy_or_sell;
            if (in >> property >> buy_or_sell) {
                game.currPlayer.improve(Property acadBuilding, string action);
            }
        } else if (command == "mortage") {
            string property_name;
            Property property_to_apply = game.findProperty();
            // not finished yet, return back to this after class of Mortage is implemented
        } else if (command == "unmortgage") {
            string property_name;
            // same for this
        } else if (command == "bankrupt") {
            game.currPlayer.bankrupt(); // fix this issue: CANNOT ACCESS THE PLAYER MEMBER FUNCTION DIRECTLY
        } else if (command == "assets") {
            game.currPlayer.assets();
        } else if (command == "all") {
            game.currPlayer.all();
        } else if (command == "save"){
            cout << "Please enter the file that you would like to save this game: " << endl;
            string file_name;
            in >> file_name;
            game.SaveGame(file_name);
        }
    }
}






