#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <map>
using namespace std;

class Board {
    // data fields
    map<string, int> players_position;

    public:
        Board();
        void draw();
        

};


#endif
