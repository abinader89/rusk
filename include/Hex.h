#include "Player.h"

struct Hex
{
    Player owner;
    int numberOfArmies;
    bool isSelected;
    bool isAdjacent;
    bool isSelectable;
    int x;
    int y;
    Hex(int newNumberOfArmies, int owner);
    Hex();
    void makeAdjacentIfPossible();
};
