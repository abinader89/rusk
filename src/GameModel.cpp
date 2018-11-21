#include "GameModel.h"

GameModel::GameModel()
{
    currentTurn = 0;
    isInReinforcementStage = false;
    currentScreen = 0;
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
    for (int i = 0; i < 2; ++i)
    {
        players.push_back(Player(i));
    }
    board[0].isSelected = true;
    board[1].isAdjacent = true;
    board[7].isAdjacent = true;
    board[8].isAdjacent = true;
}

void GameModel::updateAdjacencies(int indexOfSelected)
{
    if (indexOfSelected > 0 && indexOfSelected % boardWidth != 0)
    {
        board[indexOfSelected - 1].makeAdjacentIfPossible();
    }
    if (indexOfSelected < board.size() - 1 && indexOfSelected % boardWidth != (boardWidth - 1))
    {
        board[indexOfSelected + 1].makeAdjacentIfPossible();
    }
    if (indexOfSelected >= boardWidth)
    {
        board[indexOfSelected - boardWidth].makeAdjacentIfPossible();
        if ((indexOfSelected / boardWidth) % 2 == 0)
        {
            if (indexOfSelected % boardWidth != (boardWidth - 1))
            {
                board[indexOfSelected - boardWidth + 1].makeAdjacentIfPossible();
            }
        }
        else
        {
            if (indexOfSelected % boardWidth != 0)
            {
                board[indexOfSelected - boardWidth - 1].makeAdjacentIfPossible();
            }
        }
    }
    if (indexOfSelected < boardWidth * (boardHeight - 1))
    {
        board[indexOfSelected + boardWidth].makeAdjacentIfPossible();

        if ((indexOfSelected / boardWidth) % 2 == 0)
        {
            if (indexOfSelected % boardWidth != (boardWidth - 1))
            {
                board[indexOfSelected + boardWidth + 1].makeAdjacentIfPossible();
            }
        }
        else
        {
            if (indexOfSelected % boardWidth != 0)
            {
                board[indexOfSelected + boardWidth - 1].makeAdjacentIfPossible();
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

//0 = up
//1 = down
//2 = left
//3 = right
//TODO: this will need to change once we have more than a basic grid
void GameModel::handleSelectionChange(int direction)
{
    if (canChangeSelection(direction))
    {
        for (int i = 0; i < board.size(); ++i)
        {
            board[i].isAdjacent = false;
        }
        for (int i = 0; i < board.size(); ++i)
        {
            if (board[i].isSelected)
            {
                switch (direction)
                {
                    case 0:
                        board[i].isSelected = false;
                        board[i - boardWidth].isSelected = true;
                        updateAdjacencies(i - boardWidth);
                        break;
                    case 1:
                        board[i].isSelected = false;
                        board[i + boardWidth].isSelected = true;
                        updateAdjacencies(i + boardWidth);
                        break;
                    case 2:
                        board[i].isSelected = false;
                        board[i - 1].isSelected = true;
                        updateAdjacencies(i - 1);
                        break;
                    case 3:
                        board[i].isSelected = false;
                        board[i + 1].isSelected = true;
                        updateAdjacencies(i + 1);
                        break;
                }
                return;
            }
        }
    }
}
