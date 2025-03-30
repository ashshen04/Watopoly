#ifndef SQUARE_H
#define SQUARE_H
#include <string>
#include "observer.h"
#include "player.h"
using namespace std;

class Square : public Observer{
    string name;
    int position;

    public:
        Square(const string name, int position);
        string getName() const;
        int getPosition() const;
        virtual void action(Player &p) = 0; 
        void notify(int playpos) override;
        virtual ~Square() = default;
};

#endif