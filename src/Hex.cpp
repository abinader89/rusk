#include "Hex.h"

Hex::Hex(int player_number, int newNumberOfArmies) : owner(Player(player_number)), numberOfArmies(newNumberOfArmies) {};

Hex::Hex() : numberOfArmies(0), isSelected(false), owner(Player(3)) {};
