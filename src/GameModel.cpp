#include "GameModel.h"

GameModel::GameModel()
{
    currentTurn = 0;
    isInReinforcementStage = false;
    currentScreen = 0;
    for (int i = 0; i < 4; ++i)
    {
        board.push_back(Hex());
    }
    for (int i = 0; i < 2; ++i)
    {
        players.push_back(Player());
    }

}
