#ifndef GAME_MODEL_CXXTEST_H
#define GAME_MODEL_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "GameModel.h"

class GameModelTestSuite : public CxxTest::TestSuite
{
public:
  void testHandleSelectionChange() {
      GameModel gameModel;

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
};

#endif
