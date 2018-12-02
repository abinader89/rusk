#ifndef GAME_MODEL_CXXTEST_H
#define GAME_MODEL_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "GameModel.h"

class GameModelTestSuite : public CxxTest::TestSuite
{
public:
  void testHandleSelectionChange() {
      GameModel gameModel;
      gameModel.setupPangaeaGame();
      TS_ASSERT(gameModel.board[0].isSelected);
      //up does nothing if top
      gameModel.handleSelectionChange(0);
      TS_ASSERT(gameModel.board[0].isSelected);
      //left does nothing if far left
      gameModel.handleSelectionChange(2);
      TS_ASSERT(gameModel.board[0].isSelected);
      //right works
      gameModel.handleSelectionChange(3);
      TS_ASSERT(!gameModel.board[0].isSelected);
      TS_ASSERT(gameModel.board[1].isSelected);
      //down works
      gameModel.handleSelectionChange(1);
      TS_ASSERT(!gameModel.board[1].isSelected);
      TS_ASSERT(gameModel.board[8].isSelected);
      //now up works
      gameModel.handleSelectionChange(0);
      TS_ASSERT(!gameModel.board[8].isSelected);
      TS_ASSERT(gameModel.board[1].isSelected);
      //now left works
      gameModel.handleSelectionChange(2);
      TS_ASSERT(!gameModel.board[1].isSelected);
      TS_ASSERT(gameModel.board[0].isSelected);
      
  }

  void testNumPlayers() {
      {
          GameModel gameModelPangaea;
          gameModelPangaea.setupPangaeaGame();
          TS_ASSERT_EQUALS(gameModelPangaea.numPlayers, 4);
      }

      {
          GameModel gameModelRiver;
          gameModelRiver.setupRiverGame();
          TS_ASSERT_EQUALS(gameModelRiver.numPlayers, 2);
      }
      {
       //   GameModel gameModel_;
       //   gameModel_._()
       //   TS_ASSERT_EQUALS(gameModel_._(), 3);
      }
  }

  void testProceed() {
      GameModel test;
      test.setupRiverGame();
      test.proceed();

      TS_ASSERT(!(test.isInReinforcementStage));
      TS_ASSERT_EQUALS(test.reinforcementsLeft, 0);
  }

  void testEndAttackMode() {
      GameModel test;
      test.setupPangaeaGame();
      test.endAttackMode();

      TS_ASSERT(!(test.isInAttackMode));
  }

};

#endif
