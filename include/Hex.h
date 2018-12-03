#ifndef HEX_H
#define HEX_H

struct Hex
{
    int owner;
    int numberOfArmies;
    bool isSelected;
    bool isAdjacent;
    bool isSelectable;
    bool isAttackTarget;
    int x;
    int y;
    Hex(int newNumberOfArmies, int owner);
    Hex();
    void makeAdjacentIfPossible(int currentPlayer);
};

#endif
