#include "RiverGameModel.h"

RiverGameModel::RiverGameModel()
{
    numPlayers = 2;

    board[0].owner = 0;
    board[0].numberOfArmies = 5;
    
    board[board.size() - 1].owner = 1;
    board[board.size() - 1].numberOfArmies = 5;

    board[3].isSelectable = false;
    board[17].isSelectable = false;
    board[31].isSelectable = false;
}
