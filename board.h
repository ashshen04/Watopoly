#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <map>
using namespace std;

class Board {
    // data fields
    map<string, int> players_position;
    map<string, int> sqaures;

    public:
        Board();
        void draw();
    private:
        void InitializeBoard();
    
};

#endif
