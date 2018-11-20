#include "Hex.h"

Hex::Hex(int player_number, int newNumberOfArmies) : owner(Player(player_number)), numberOfArmies(newNumberOfArmies) {};

Hex::Hex() : owner(Player(3)), numberOfArmies(0), isSelected(false) {};
