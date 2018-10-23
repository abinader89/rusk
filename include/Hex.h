#include "Player.h"

struct Hex
{
    Player owner;
    int numberOfDice;
    int reinforced;
    Hex(int newNumberOfDice);
    Hex();
};
