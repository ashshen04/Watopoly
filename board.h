#ifndef BOARD_H
#define BOARD_H

#include <string>

#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include "academic.h"
using namespace std;


// Board class that takes the role of view in MVC model 
class Board : public Observer{
  // Stores the visual representation of the board in the form of strings
  vector<vector<string>> board;
  map<char, int> playerPos;

  public:
    Board();

    // Updates the improvement information stored in the board 
    void notify(int position, int improveNum, int oldp, int newp, char c);
    void updatePlayer(int oldPosition, int newPosition, char player);
    void removePlayer(int position, char player);
    void drawBoard(ostream & out);
};

#endif
