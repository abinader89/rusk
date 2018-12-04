#include "GameModel.h"
#include <stdlib.h>

GameModel::GameModel()
{
    winner = -1;
    currentTurn = 0;
    isInReinforcementStage = true;
    isInAttackMode = false;
    reinforcementsLeft = 0;
    boardWidth = 7;
    boardHeight = 5;
    maxArmiesPerHex = 20;
    for (int i = 0; i < (boardWidth * boardHeight); ++i)
    {
        Hex currentHex;
        currentHex.isSelectable = true;
        currentHex.x = 100 * (i % boardWidth) + (50 * (((i / boardWidth) + 1) % 2));
        currentHex.y = (i / boardWidth) * 100 + 200;

        board.push_back(currentHex);
    }
    board[0].isSelected = true;
    currentSelectedIndex = 0;
    currentAttackTargetIndex = -1;
    board[1].isAdjacent = true;
    board[7].isAdjacent = true;
    board[8].isAdjacent = true;
}


void GameModel::updateAdjacencies()
{
    if (board[currentSelectedIndex].isSelectable)
    {
        if (currentSelectedIndex > 0 && currentSelectedIndex % boardWidth != 0)
        {
            board[currentSelectedIndex - 1].makeAdjacentIfPossible(currentTurn % numPlayers);
        }
        if (currentSelectedIndex < board.size() - 1 && currentSelectedIndex % boardWidth != (boardWidth - 1))
        {
            board[currentSelectedIndex + 1].makeAdjacentIfPossible(currentTurn % numPlayers);
        }
        if (currentSelectedIndex >= boardWidth)
        {
            board[currentSelectedIndex - boardWidth].makeAdjacentIfPossible(currentTurn % numPlayers);
            if ((currentSelectedIndex / boardWidth) % 2 == 0)
            {
                if (currentSelectedIndex % boardWidth != (boardWidth - 1))
                {
                    board[currentSelectedIndex - boardWidth + 1].makeAdjacentIfPossible(currentTurn % numPlayers);
                }
            }
            else
            {
                if (currentSelectedIndex % boardWidth != 0)
                {
                    board[currentSelectedIndex - boardWidth - 1].makeAdjacentIfPossible(currentTurn % numPlayers);
                }
            }
        }
        if (currentSelectedIndex < boardWidth * (boardHeight - 1))
        {
            board[currentSelectedIndex + boardWidth].makeAdjacentIfPossible(currentTurn % numPlayers);

            if ((currentSelectedIndex / boardWidth) % 2 == 0)
            {
                if (currentSelectedIndex % boardWidth != (boardWidth - 1))
                {
                    board[currentSelectedIndex + boardWidth + 1].makeAdjacentIfPossible(currentTurn % numPlayers);
                }
            }
            else
            {
                if (currentSelectedIndex % boardWidth != 0)
                {
                    board[currentSelectedIndex + boardWidth - 1].makeAdjacentIfPossible(currentTurn % numPlayers);
                }
            }
        }
    }
}

//0 = up
//1 = down
//2 = left
//3 = right
bool GameModel::canChangeSelection(int direction)
{

    switch (direction)
    {
        case 0:
            return currentSelectedIndex >= boardWidth;
        case 1:
            return (currentSelectedIndex < boardWidth * (boardHeight - 1));
        case 2:
            return (currentSelectedIndex > 0);
        case 3:
            return (currentSelectedIndex < board.size() - 1);
        //shouldn't happen - just here to suppress warning (will get fixed once we use class enums)
        default:
            return false;
    }
}

bool GameModel::canChangeAttackTarget(int direction)
{
    switch (direction)
    {
        case 0:
            return currentAttackTargetIndex >= boardWidth;
        case 1:
            return (currentAttackTargetIndex < boardWidth * (boardHeight - 1));
        case 2:
            return (currentAttackTargetIndex > 0);
        case 3:
            return (currentAttackTargetIndex < board.size() - 1);
        //shouldn't happen - just here to suppress warning (will get fixed once we use class enums)
        default:
            return false;
    }
}

//0 = up
//1 = down
//2 = left
//3 = right
void GameModel::handleSelectionChange(int direction)
{
    if (isInAttackMode)
    {
        if (currentAttackTargetIndex != -1 && canChangeAttackTarget(direction))
        {
            switch (direction)
            {
                case 0:
                    if (board[currentAttackTargetIndex - boardWidth].isAdjacent)
                    {
                        board[currentAttackTargetIndex].isAttackTarget = false;
                        board[currentAttackTargetIndex - boardWidth].isAttackTarget = true;
                        currentAttackTargetIndex = currentAttackTargetIndex - boardWidth;
                    }
                    if (board[currentAttackTargetIndex - boardWidth].isSelected)
                    {
                        board[currentAttackTargetIndex].isAttackTarget = false;
                        currentAttackTargetIndex = -1;
                    }
                    break;
                case 1:
                    if (board[currentAttackTargetIndex + boardWidth].isAdjacent)
                    {
                        board[currentAttackTargetIndex].isAttackTarget = false;
                        board[currentAttackTargetIndex + boardWidth].isAttackTarget = true;
                        currentAttackTargetIndex = currentAttackTargetIndex + boardWidth;
                    }
                    if (board[currentAttackTargetIndex + boardWidth].isSelected)
                    {
                        board[currentAttackTargetIndex].isAttackTarget = false;
                        currentAttackTargetIndex = -1;
                    }
                    break;
                case 2:
                    if (board[currentAttackTargetIndex - 1].isAdjacent)
                    {
                        board[currentAttackTargetIndex].isAttackTarget = false;
                        board[currentAttackTargetIndex - 1].isAttackTarget = true;
                        currentAttackTargetIndex = currentAttackTargetIndex - 1;
                    }
                    if (board[currentAttackTargetIndex - 1].isSelected)
                    {
                        board[currentAttackTargetIndex].isAttackTarget = false;
                        currentAttackTargetIndex = -1;
                    }
                    break;
                case 3:
                    if (board[currentAttackTargetIndex + 1].isAdjacent)
                    {
                        board[currentAttackTargetIndex].isAttackTarget = false;
                        board[currentAttackTargetIndex + 1].isAttackTarget = true;
                        currentAttackTargetIndex = currentAttackTargetIndex + 1;
                    }
                    if (board[currentAttackTargetIndex + 1].isSelected)
                    {
                        board[currentAttackTargetIndex].isAttackTarget = false;
                        currentAttackTargetIndex = -1;
                    }
                    break;
            }
            return;
        }
        if (canChangeSelection(direction))
        {
            switch (direction)
            {
                case 0:
                    if (board[currentSelectedIndex - boardWidth].isAdjacent)
                    {
                        board[currentSelectedIndex - boardWidth].isAttackTarget = true;
                        currentAttackTargetIndex = currentSelectedIndex - boardWidth;
                    }
                    break;
                case 1:
                    if (board[currentSelectedIndex + boardWidth].isAdjacent)
                    {
                        board[currentSelectedIndex + boardWidth].isAttackTarget = true;
                        currentAttackTargetIndex = currentSelectedIndex + boardWidth;
                    }
                    break;
                case 2:
                    if (board[currentSelectedIndex - 1].isAdjacent)
                    {
                        board[currentSelectedIndex - 1].isAttackTarget = true;
                        currentAttackTargetIndex = currentSelectedIndex - 1;
                    }
                    break;
                case 3:
                    if (board[currentSelectedIndex + 1].isAdjacent)
                    {
                        board[currentSelectedIndex + 1].isAttackTarget = true;
                        currentAttackTargetIndex = currentSelectedIndex + 1;
                    }
                    break;
            }
            return;
        }
    }
    else
    {

        if (canChangeSelection(direction))
        {
            for (int i = 0; i < board.size(); ++i)
            {
                board[i].isAdjacent = false;
            }
            board[currentSelectedIndex].isSelected = false;
            switch (direction)
            {
                case 0:
                    board[currentSelectedIndex - boardWidth].isSelected = true;
                    currentSelectedIndex = currentSelectedIndex - boardWidth;
                    updateAdjacencies();
                    break;
                case 1:
                    board[currentSelectedIndex + boardWidth].isSelected = true;
                    currentSelectedIndex = currentSelectedIndex + boardWidth;
                    updateAdjacencies();
                    break;
                case 2:
                    board[currentSelectedIndex - 1].isSelected = true;
                    currentSelectedIndex = currentSelectedIndex - 1;
                    updateAdjacencies();
                    break;
                case 3:
                    board[currentSelectedIndex + 1].isSelected = true;
                    currentSelectedIndex = currentSelectedIndex + 1;
                    updateAdjacencies();
                    break;
            }
            return;
        }
    }
}

void GameModel::calculateReinforcements()
{
    for (int i = 0; i < board.size(); ++i)
    {
        if (board[i].owner == currentTurn % numPlayers)
        {
            ++reinforcementsLeft;
        }
    }
}

void GameModel::proceed()
{
    if (isInReinforcementStage)
    {
        isInReinforcementStage = false;
    }
    else
    {
        endAttackMode();
        isInReinforcementStage = true;
        reinforcementsLeft = 0;
        while (reinforcementsLeft == 0)
        {
            ++currentTurn;
            calculateReinforcements();
        }
    }
}

void GameModel::checkForWinner()
{
    std::vector<int> hexesLeft;
    for (int i = 0; i < numPlayers; ++i)
    {
        hexesLeft.push_back(0);
    }
    for (int i = 0; i < board.size(); ++i)
    {
        if (board[i].owner != -1)
        {
            ++hexesLeft[board[i].owner];
        }
    }
    int playersLeft = 0;
    int winnerIfDone = -1;
    for (int i = 0; i < hexesLeft.size(); ++i)
    {
        if (hexesLeft[i] > 0)
        {
            ++playersLeft;
            winnerIfDone = i;
        }
    }
    if (playersLeft == 1)
    {
        winner = winnerIfDone;
    }
}

void GameModel::enterAttackMode()
{
    isInAttackMode = true;
}

void GameModel::endAttackMode()
{
    for (int i = 0; i < board.size(); ++i)
    {
        board[i].isAttackTarget = false;
        currentAttackTargetIndex = -1;
    }
    isInAttackMode = false;
    checkForWinner();
}

void GameModel::reinforce()
{
    if (board[currentSelectedIndex].owner == currentTurn % numPlayers)
    {
        if (reinforcementsLeft > 0 &&
            board[currentSelectedIndex].numberOfArmies < maxArmiesPerHex)
        {
            ++board[currentSelectedIndex].numberOfArmies;
            --reinforcementsLeft;
        }
    }
}

void GameModel::attack()
{
    int attackerTotalRoll = 0;
    int defenderTotalRoll = 0;

    for (int i = 0; i < board[currentSelectedIndex].numberOfArmies; ++i)
    {
        attackerTotalRoll += rand() % 6 + 1;
    }
    for (int i = 0; i < board[currentAttackTargetIndex].numberOfArmies; ++i)
    {
        defenderTotalRoll += rand() % 6 + 1;
    }

    if (attackerTotalRoll > defenderTotalRoll)
    {
        board[currentAttackTargetIndex].owner = currentTurn % numPlayers;
        board[currentAttackTargetIndex].isAdjacent = false;
        board[currentAttackTargetIndex].numberOfArmies = board[currentSelectedIndex].numberOfArmies - 1;
    }
    board[currentSelectedIndex].numberOfArmies = 1;
    endAttackMode();
}

void GameModel::handleSelect()
{
    if (!isInReinforcementStage)
    {
        if (currentAttackTargetIndex != -1)
        {
            attack();
            return;
        }
        else if (board[currentSelectedIndex].owner == currentTurn % numPlayers &&
            board[currentSelectedIndex].numberOfArmies > 1)
        {
            enterAttackMode();
        }
    }
    else
    {
        reinforce();
    }
}
