#ifndef SQUARE_H
#define SQUARE_H
#include <string>
#include "player.h"
using namespace std;

class Square {
    string name;
    int position;

    public:
        Square(const string name, int position);
        string getName() const;
        int getPosition() const;
        virtual void action(Player &p) = 0; 
        virtual ~Square() = 0;
};

#endif