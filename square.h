#ifndef SQUARE_H
#define SQUARE_H
#include <string>
#include "player.h"
#include "observer.h"
using namespace std;

class Player;

class Square : public Observer {
    protected:
    string name;
    int position;

    public:
        Square(const string name, int position);
        string getName() const;
        int getPosition() const;
        virtual void action(Player &p) = 0; 
        void notify(int playpos, int temp, int a, int b, char c) override;
        virtual ~Square() = default;
};

#endif
