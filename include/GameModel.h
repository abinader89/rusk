#include "Hex.h"

#include <vector>

struct GameModel
{
    std::vector<Hex> board;
    std::vector<Player> players;
    int currentTurn;
    bool isInReinforcementStage;
    int currentScreen;
    int boardWidth;
    int boardHeight;

    GameModel();
    void handleSelectionChange(int direction);
};
