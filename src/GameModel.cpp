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
    for (int i = 0; i < (boardWidth * boardHeight); ++i)
    {
        Hex currentHex;
        currentHex.isSelectable = true;
        currentHex.x = 100 * (i % boardWidth) + (50 * (((i / boardWidth) + 1) % 2));
        currentHex.y = (i / boardWidth) * 100 + 200;

        board.push_back(currentHex);
    }
}

void GameModel::setupPangaeaGame()
{
    numPlayers = 4;
    board[0].isSelected = true;
    board[1].isAdjacent = true;
    board[7].isAdjacent = true;
    board[8].isAdjacent = true;

    board[0].owner = 0;
    board[0].numberOfArmies = 5;

    board[boardWidth - 1].owner = 1;
    board[boardWidth - 1].numberOfArmies = 5;

    board[board.size() - boardWidth].owner = 2;
    board[board.size() - boardWidth].numberOfArmies = 5;

    board[board.size() - 1].owner = 3;
    board[board.size() - 1].numberOfArmies = 5;
}

void GameModel::setupRiverGame()
{
    numPlayers = 2;
    board[0].isSelected = true;
    board[1].isAdjacent = true;
    board[7].isAdjacent = true;
    board[8].isAdjacent = true;

    board[0].owner = 0;
    board[0].numberOfArmies = 5;
    board[board.size() - 1].owner = 1;
    board[board.size() - 1].numberOfArmies = 5;

    board[3].isSelectable = false;
    board[17].isSelectable = false;
    board[31].isSelectable = false;

}


void GameModel::updateAdjacencies(int indexOfSelected)
{
    if (board[indexOfSelected].isSelectable)
    {
        if (indexOfSelected > 0 && indexOfSelected % boardWidth != 0)
        {
            board[indexOfSelected - 1].makeAdjacentIfPossible(currentTurn % numPlayers);
        }
        if (indexOfSelected < board.size() - 1 && indexOfSelected % boardWidth != (boardWidth - 1))
        {
            board[indexOfSelected + 1].makeAdjacentIfPossible(currentTurn % numPlayers);
        }
        if (indexOfSelected >= boardWidth)
        {
            board[indexOfSelected - boardWidth].makeAdjacentIfPossible(currentTurn % numPlayers);
            if ((indexOfSelected / boardWidth) % 2 == 0)
            {
                if (indexOfSelected % boardWidth != (boardWidth - 1))
                {
                    board[indexOfSelected - boardWidth + 1].makeAdjacentIfPossible(currentTurn % numPlayers);
                }
            }
            else
            {
                if (indexOfSelected % boardWidth != 0)
                {
                    board[indexOfSelected - boardWidth - 1].makeAdjacentIfPossible(currentTurn % numPlayers);
                }
            }
        }
        if (indexOfSelected < boardWidth * (boardHeight - 1))
        {
            board[indexOfSelected + boardWidth].makeAdjacentIfPossible(currentTurn % numPlayers);

            if ((indexOfSelected / boardWidth) % 2 == 0)
            {
                if (indexOfSelected % boardWidth != (boardWidth - 1))
                {
                    board[indexOfSelected + boardWidth + 1].makeAdjacentIfPossible(currentTurn % numPlayers);
                }
            }
            else
            {
                if (indexOfSelected % boardWidth != 0)
                {
                    board[indexOfSelected + boardWidth - 1].makeAdjacentIfPossible(currentTurn % numPlayers);
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
    for (int i = 0; i < board.size(); ++i)
    {
        if (board[i].isSelected)
        {
            switch (direction)
            {
                case 0:
                    return i >= boardWidth;
                case 1:
                    return (i < boardWidth * (boardHeight - 1));
                case 2:
                    return (i > 0);
                case 3:
                    return (i < board.size() - 1);
            }
        }
    }
    return false;
}

bool GameModel::canChangeAttackTarget(int direction)
{
    for (int i = 0; i < board.size(); ++i)
    {
        if (board[i].isAttackTarget)
        {
            switch (direction)
            {
                case 0:
                    return i >= boardWidth;
                case 1:
                    return (i < boardWidth * (boardHeight - 1));
                case 2:
                    return (i > 0);
                case 3:
                    return (i < board.size() - 1);
            }
        }
    }
    return false;
}

//0 = up
//1 = down
//2 = left
//3 = right
//TODO: this will need to change once we have more than a basic grid
void GameModel::handleSelectionChange(int direction)
{
    if (isInAttackMode)
    {
        for (int i = 0; i < board.size(); ++i)
        {
            if (board[i].isAttackTarget && canChangeAttackTarget(direction))
            {
                switch (direction)
                {
                    case 0:
                        if (board[i - boardWidth].isAdjacent)
                        {
                            board[i].isAttackTarget = false;
                            board[i - boardWidth].isAttackTarget = true;
                        }
                        if (board[i - boardWidth].isSelected)
                        {
                            board[i].isAttackTarget = false;
                        }
                        break;
                    case 1:
                        if (board[i + boardWidth].isAdjacent)
                        {
                            board[i].isAttackTarget = false;
                            board[i + boardWidth].isAttackTarget = true;
                        }
                        if (board[i + boardWidth].isSelected)
                        {
                            board[i].isAttackTarget = false;
                        }
                        break;
                    case 2:
                        if (board[i - 1].isAdjacent)
                        {
                            board[i].isAttackTarget = false;
                            board[i - 1].isAttackTarget = true;
                        }
                        if (board[i - 1].isSelected)
                        {
                            board[i].isAttackTarget = false;
                        }
                        break;
                    case 3:
                        if (board[i + 1].isAdjacent)
                        {
                            board[i].isAttackTarget = false;
                            board[i + 1].isAttackTarget = true;
                        }
                        if (board[i + 1].isSelected)
                        {
                            board[i].isAttackTarget = false;
                        }
                        break;
                }
                return;
            }
        }
        for (int i = 0; i < board.size(); ++i)
        {
            if (board[i].isSelected && canChangeSelection(direction))
            {
                switch (direction)
                {
                    case 0:
                        if (board[i - boardWidth].isAdjacent)
                        {
                            board[i - boardWidth].isAttackTarget = true;
                        }
                        break;
                    case 1:
                        if (board[i + boardWidth].isAdjacent)
                        {
                            board[i + boardWidth].isAttackTarget = true;
                        }
                        break;
                    case 2:
                        if (board[i - 1].isAdjacent)
                        {
                            board[i - 1].isAttackTarget = true;
                        }
                        break;
                    case 3:
                        if (board[i + 1].isAdjacent)
                        {
                            board[i + 1].isAttackTarget = true;
                        }
                        break;
                }
                return;
            }
        }
    }
    else
    {
        for (int i = 0; i < board.size(); ++i)
        {
            if (board[i].isSelected && canChangeSelection(direction))
            {
                for (int i = 0; i < board.size(); ++i)
                {
                    board[i].isAdjacent = false;
                }
                board[i].isSelected = false;
                switch (direction)
                {
                    case 0:
                        board[i - boardWidth].isSelected = true;
                        updateAdjacencies(i - boardWidth);
                        break;
                    case 1:
                        board[i + boardWidth].isSelected = true;
                        updateAdjacencies(i + boardWidth);
                        break;
                    case 2:
                        board[i - 1].isSelected = true;
                        updateAdjacencies(i - 1);
                        break;
                    case 3:
                        board[i + 1].isSelected = true;
                        updateAdjacencies(i + 1);
                        break;
                }
                return;
            }
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
    }
    isInAttackMode = false;
    checkForWinner();
}

void GameModel::reinforce(int reinforceTargetIndex)
{
    if (board[reinforceTargetIndex].isSelected &&
        board[reinforceTargetIndex].owner == currentTurn % numPlayers)
    {
        if (reinforcementsLeft > 0)
        {
            ++board[reinforceTargetIndex].numberOfArmies;
            --reinforcementsLeft;
        }
    }
}

void GameModel::attack(int attackTargetIndex)
{
    int attackerIndex = -1;
    int attackerTotalRoll = 0;
    int defenderTotalRoll = 0;
    for (int i = 0; i < board.size(); ++i)
    {
        if (board[i].isSelected)
        {
            attackerIndex = i;
            for (int j = 0; j < board[i].numberOfArmies; ++j)
            {
                attackerTotalRoll += rand() % 6 + 1;
            }
        }
    }
    for (int i = 0; i < board[attackTargetIndex].numberOfArmies; ++i)
    {
        defenderTotalRoll += rand() % 6 + 1;
    }

    if (attackerTotalRoll > defenderTotalRoll)
    {
        board[attackTargetIndex].owner = currentTurn % numPlayers;
        board[attackTargetIndex].isAdjacent = false;
        board[attackTargetIndex].numberOfArmies = board[attackerIndex].numberOfArmies - 1;
    }
    board[attackerIndex].numberOfArmies = 1;
    endAttackMode();
}

void GameModel::handleSelect()
{
    if (!isInReinforcementStage)
    {
        for (int i = 0; i < board.size(); ++i)
        {
            if (board[i].isAttackTarget)
            {
                attack(i);
                return;
            }
        }
    }
    for (int i = 0; i < board.size(); ++i)
    {
        if (board[i].isSelected && isInReinforcementStage)
        {
            reinforce(i);
            return;
        }
        else
        {
            if (board[i].isSelected && board[i].owner == currentTurn % numPlayers && board[i].numberOfArmies > 1)
            {
                enterAttackMode();
                return;
            }
        }
    }
}
