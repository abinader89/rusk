#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "Hex.h"
#include <vector>

struct GameModel
{
    std::vector<Hex> board;
    int numPlayers;
    int currentTurn;
    bool isInReinforcementStage;
    int reinforcementsLeft;
    bool isInAttackMode;
    int boardWidth;
    int boardHeight;
    int winner;
    int maxArmiesPerHex;


    void handleSelectionChange(int direction);
    void handleSelect();
    void proceed();
    void endAttackMode();

private:
    int currentSelectedIndex;
    int currentAttackTargetIndex;

    void updateAdjacencies();
    void reinforce();
    void enterAttackMode();
    void attack();
    bool canChangeSelection(int direction);
    bool canChangeAttackTarget(int direction);
    void endGameWithWinner(int winningPlayer);
    void checkForWinner();
    void calculateReinforcements();

protected:
    GameModel();
};

#endif
