#include "Player.h"

struct Hex
{
    Player owner;
    int numberOfDice;
    Hex(int newNumberOfDice);
    Hex();
};
