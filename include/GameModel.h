#include "Hex.h"

#include <vector>

struct GameModel
{
    std::vector<Hex> board;
    std::vector<Player> players;
    int currentTurn;
    bool isInReinforcementStage;
    int currentScreen;

    GameModel();
};
