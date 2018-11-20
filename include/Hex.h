#include "Player.h"

struct Hex
{
    Player owner;
    int numberOfArmies;
    bool isSelected;
    int x;
    int y;
    Hex(int newNumberOfArmies, int owner);
    Hex();
};
