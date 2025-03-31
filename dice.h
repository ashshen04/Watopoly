#ifndef DICE_H
#define DICE_H

class Dice {
    int dice1;
    int dice2;

    public:
        int roll();
        int testroll(int d1, int d2);
        bool isDouble();
};

#endif

