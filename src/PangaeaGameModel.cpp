#include "PangaeaGameModel.h"

PangaeaGameModel::PangaeaGameModel()
{
    numPlayers = 4;

    board[0].owner = 0;
    board[0].numberOfArmies = 5;

    board[boardWidth - 1].owner = 1;
    board[boardWidth - 1].numberOfArmies = 5;

    board[board.size() - boardWidth].owner = 2;
    board[board.size() - boardWidth].numberOfArmies = 5;

    board[board.size() - 1].owner = 3;
    board[board.size() - 1].numberOfArmies = 5;
}
