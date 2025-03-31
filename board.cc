#include "board.h"
#include "academic.h"
#include "player.h"

const int SquareLen=9;
const int NumSquare=40;
using namespace std;

map <int, string> academic = {
    {1, "AL     "},{3, "ML     "},{6, "ECH    "},{8, "PAS    "},
    {9, "HH     "},{11, "RCH    "},{13, "DWE    "},{14, "CPH    "},
    {16, "LHI    "},{18, "BMH    "},{19, "OPT    "},{21, "EV1    "},
    {23, "EV2    "},{24, "EV3    "},{26, "PHYS   "},{27, "B1     "},
    {29, "B2     "},{31, "EIT    "},{32, "ESC    "},{34, "C2     "},
    {37, "MC     "},{39, "DC     "}
};

// map that stores the information of all twoLine buildings
const map <int, vector<string>> twoLine = {
  {0, {"COLLECT", "OSAP   "}},{7, {"NEEDLES", "HALL   "}},
  {10, {"DC Tims", "Line   "}},{20, {"Goose  ", "Nesting"}},
  {22, {"NEEDLES", "HALL   "}},
  {30, {"GO TO  ", "TIMS   "}},{36, {"NEEDLES", "HALL   "}},
  {38, {"COOP   ", "FEE    "}}
};

// map that stores the information of all other buildings
const map <int, string> other = {
  {2, "SLC    "},{4, "TUITION"}, {5, "MKV    "},
  {12, "PAC    "}, {15, "UWP    "}, {17, "SLC    "},
  {25, "V1     "},{28, "CIF    "}, {33, "SLC    "},
  {35, "REV    "}
};

const vector<string> waterlooArt = {
    "| #   #  ##  #####  ###  ###   ###  #  #   # |",
    "| #   # #  #   #   #   # #  # #   # #  #   # |",
    "| # # # ####   #   #   # ###  #   # #   # #  |",
    "| # # # #  #   #   #   # #    #   # #    #   |",
    "| ##### #  #   #    ###  #     ###  ###  #   |"
};



Board::Board() {
	vector<string> piece(SquareLen-2, "");
	board = vector<vector<string>>(NumSquare, piece);

	for (int i = 0; i < NumSquare; i++) {	
		if (academic.count(i) == 1) {
			board[i][0] = " ------- ";
      			board[i][1] = "|       |";
      			board[i][2] = "|-------|";
      			board[i][3] = "|" + academic[i] + "|";
      			board[i][4] = "|       |";
      			board[i][5] = "|       |";
      			board[i][6] = " ------- ";
    		} else if (twoLine.count(i) == 1) {
      			board[i][0] = " ------- ";
      			board[i][1] = "|" + twoLine.at(i)[0] + "|";
      			board[i][2] = "|" + twoLine.at(i)[1] + "|";
      			board[i][3] = "|       |";
      			board[i][4] = "|       |";
      			board[i][5] = "|       |";
      			board[i][6] = " ------- ";
    		} else {
      			board[i][0] = " ------- ";
      			board[i][1] = "|" + other.at(i) + "|";
      			board[i][2] = "|       |";
      			board[i][3] = "|       |";
      			board[i][4] = "|       |";
      			board[i][5] = "|       |";
      			board[i][6] = " ------- ";
		}
	}
}


void Board::notify(int position, int improveNum, int oldP, int newP, char player) {
	string temp = "|       |";
	for (int i = 0; i < improveNum; i++) {
	  temp[i + 1] = 'I';
	}
	board[position][1] = temp;
	updatePlayer(oldP, newP, player);
}

void Board::updatePlayer(int oldPosition, int newPosition, char player) {
	// for initial representation of players' position
	if (!((oldPosition == 0) && (newPosition == 0))) {
		for (int i = 1; i < SquareLen; i ++) {
			if (board[oldPosition][4][i] == player) {
			board[oldPosition][4][i] = ' ';
			}
		}
		for (int i = 1; i < SquareLen; i ++) {
			if (board[oldPosition][5][i] == player) {
			board[oldPosition][5][i] = ' ';
			}
		}
	}
	
	for (int i = 1; i < SquareLen; i ++) {
		if (board[newPosition][4][i] == ' ') {
		board[newPosition][4][i] = player;
		return;
		}
	}
	for (int i = 1; i < SquareLen; i ++) {
		if (board[newPosition][5][i] == ' ') {
		board[newPosition][5][i] = player;
		return;
		}
	}
}

void Board::removePlayer(int position, char player) {
	for (int i = 1; i < SquareLen; i ++) {
		if (board[position][4][i] == player) {
			board[position][4][i] = ' ';
		}
	}
			
	for (int i = 1; i < SquareLen; i ++) {
		if (board[position][5][i] == player) {
			board[position][5][i] = ' ';
		}
	}
}
	



void Board::drawBoard(ostream & out) {
  for (int h = 0; h < 7; h++) {
    for (int w = 20; w <= 30; w++) {
      out << board[w][h];
    }
    out << "\n";
  }
  
  for (int i = 19; i > 10; i--) {
    for (int h = 0; h < 7; h++) {
      // Check if current position is the central row (i=15) and within art lines
      if (i == 15 && h >= 1 && h <= 5) {
        out << board[i][h]; // Left square (UWP)
        out << "                  " << waterlooArt[h-1] << "                 "; 
        out << board[40 - i + 10][h] << "\n"; // Right square (REV)
      } else {
        out << board[i][h]; // Left square
        out << setw(81) << ""; // Spacing
        out << board[40 - i + 10][h] << "\n"; // Right square
      }
    }
  }
  
  for (int h = 0; h < 7; h++) {
    for (int w = 10; w >= 0; w--) {
      out << board[w][h];
    }
    out << "\n";
  }
}


