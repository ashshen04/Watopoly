#ifndef TIMSLINE_H
#define TIMSLINE_H
#include <iostream>
#include <string>
#include "dice.h"
#include "rolluprimcup.h"
#include "player.h"
#include "nonproperty.h"
using namespace std;

class TimsLine : public NonProperty {
    public:
        TimsLine(string name, int pos) : NonProperty{name, pos} {}
        void action(Player& p) override {
            cout << "Player" << p.getChar() << " is at the DC Tims Line. Nothing happens." << endl;
        }

        void LineAction(Player &p, Dice &dice) {
            if (!p.getinTims()) return;

            // if in Tims Line situation:
            if (p.AddTimsTurn() == 3) {
                leaveLine(p, dice);
                return;
            }
            
            cout << "Player " << p.getChar() << " is in the DC Tims Line. Choose an action to leave:" << endl;
            cout << "1. Roll dice to try for doubles" << endl;
            cout << "2. Pay $50" << endl;
            cout << "3. Use a cup (if available)" << endl;

            string command;
            cin >> command;
            
            if (command == "1") {
                int roll = dice.roll();
                if (dice.isDouble()) {
                    p.outofTims();
                    p.move(roll);
                } else {
                    cout << "Player " << p.getChar() << " did not roll doubles :( and remains in the DC Tims Line." << endl;
                }
            } else if (command == "2") {
                if (p.getMoney() >= 50) {
                    cout << "Player " << p.getChar() << " pays $50 to leave the DC Tims Line." << endl;
                    p.SubMoney(50);
                    p.outofTims();
                    int roll = dice.roll();
                    p.move(roll);
                    cout << "Player " << p.getChar() << " moves " << roll << " space(s)" << endl;
                } else {
                    cout << "Error: Player " << p.getChar() << " does not have enough money to pay $50." << endl;
                }
            } else if (command == "3") {
                if (p.getTimsCup() > 0) {
                    cout << "Player " << p.getChar() << " uses a roll up the rim cup to leave the DC Tims Line." << endl;
                    RollUpRimCup::useCup(p);
                    p.outofTims();
                    int roll = dice.roll();
                    p.move(roll);
                    cout << "Player " << p.getChar() << " moves " << roll << " space(s)." << endl;
                } else {
                    cout << "Error: Player " << p.getChar() << " does not have a roll up the rim cup." << endl;
                }
            } else {
                cout << "Invalid command. Please re-enter the options" << endl;
            }
        }

    private:
        void leaveLine(Player &p, Dice &dice) {
            cout << "Player " << p.getChar() << " has been in Tims Line for 3 round. Must leave and moves!!" << endl;
            cout << "Choose an action to leave:" << endl;
            cout << "1. Pay $50" << endl;
            cout << "2. Use a cup (if available)" << endl;

            string command;
            cin >> command;

            if (command == "2") {
                if (p.getTimsCup() > 0) {
                    cout << "Player " << p.getChar() << " uses a Roll Up the Rim cup to leave the DC Tims Line." << endl;
                    RollUpRimCup::useCup(p);
                } else {
                    cout << "Player " << p.getChar() << " does not have a Roll Up the Rim cup. Forced to pay $50." << endl;
                    p.SubMoney(50);
                    if (&p == nullptr) return;
                }
            } else if (command != "1") {
                cout << "Invalid command. Player " << p.getChar() << " remains in the DC Tims Line." << endl;
                return;
            } else { // command == "1"
                p.SubMoney(50); // in this case if money is enough, the player pays $50 else it enter the situation of auction or mortgage.
                
            }

            if (&p == nullptr) return;

            p.outofTims();
            int roll = dice.roll();
            p.move(roll);
            cout << "Player " << p.getChar() << " moves " << roll << " space(s)." << endl;
        }
};

#endif