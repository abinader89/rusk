#include "RingGameModel.h"

RingGameModel::RingGameModel()
{
    numPlayers = 3;

    board[0].owner = 0;
    board[0].numberOfArmies = 5;

    board[13].owner = 1;
    board[13].numberOfArmies = 5;

    board[30].owner = 2;
    board[30].numberOfArmies = 5;

    board[9].isSelectable = false;
    board[10].isSelectable = false;
    board[11].isSelectable = false;

    board[16].isSelectable = false;
    board[17].isSelectable = false;
    board[18].isSelectable = false;

    board[23].isSelectable = false;
    board[24].isSelectable = false;
    board[25].isSelectable = false;



}
