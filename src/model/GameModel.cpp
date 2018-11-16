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
        currentHex.x = 100 * (i % boardWidth) + (50 * (((i / boardWidth) + 1) % 2));
        currentHex.y = (i / boardWidth) * 100 + 200;

        board.push_back(currentHex);
    }
    for (int i = 0; i < 2; ++i)
    {
        players.push_back(Player());
    }
}

//0 = up
//1 = down
//2 = left
//3 = right
//TODO: this will need to change once we have more than a basic grid
void GameModel::handleSelectionChange(int direction)
{
    for (int i = 0; i < board.size(); ++i)
    {
        if (board[i].isSelected)
        {
            switch (direction)
            {
                case 0:
                    if (i >= boardWidth)
                    {
                        board[i].isSelected = false;
                        board[i - boardWidth].isSelected = true;
                    }
                    break;
                case 1:
                    if (i < boardWidth * (boardHeight - 1))
                    {
                        board[i].isSelected = false;
                        board[i + boardWidth].isSelected = true;
                    }
                    break;
                case 2:
                    if (i > 0)
                    {
                        board[i].isSelected = false;
                        board[i - 1].isSelected = true;
                    }
                    break;
                case 3:
                    if (i < board.size() - 1)
                    {
                        board[i].isSelected = false;
                        board[i + 1].isSelected = true;
                    }
                    break;
            }
            return;
        }
    }

}
