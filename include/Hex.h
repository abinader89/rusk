#include "Player.h"

struct Hex
{
    Player owner;
    int numberOfDice;
    int reinforced;
    bool isSelected;
    int x;
    int y;
    Hex(int newNumberOfDice);
    Hex();
};
