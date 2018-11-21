#include "Player.h"

struct Hex
{
    Player owner;
    int numberOfDice;
    int reinforced;
    bool isSelected;
    bool isAdjacent;
    bool isSelectable;
    int x;
    int y;
    Hex(int newNumberOfDice);
    Hex();
    void makeAdjacentIfPossible();
};
