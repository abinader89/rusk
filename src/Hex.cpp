#include "Hex.h"

Hex::Hex(int player_number, int newNumberOfArmies) : owner(player_number), numberOfArmies(newNumberOfArmies) {};

Hex::Hex() : owner(-1), numberOfArmies(0), isSelected(false), isAttackTarget(false) {};

void Hex::makeAdjacentIfPossible(int currentPlayer)
{
    if (isSelectable && currentPlayer != owner)
    {
        isAdjacent = true;
    }
}
