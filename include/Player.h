#include <iostream>

struct Player
{
    bool currentTurn;
    int draftCount;
    int player_number;

    Player(int player_number) : player_number(player_number) {}

bool isCurrentTurn()
{
    return currentTurn;
}

int getDraftCount()
{
    return draftCount;
}
};


