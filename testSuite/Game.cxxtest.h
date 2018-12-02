#ifndef GAME_CXXTEST_H
#define GAME_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "Game.h"

class GameTestSuite : public CxxTest::TestSuite
{
    public:
    void testConstructorInstantiatesModel() {
        Game test_game;
        TS_ASSERT(test_game.getGameModel());
    }
};

#endif
