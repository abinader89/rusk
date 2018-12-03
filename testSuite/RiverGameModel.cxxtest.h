#ifndef RIVER_GAME_MODEL_CXXTEST_H
#define RIVER_GAME_MODEL_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "Hex.h"
#include "RiverGameModel.h"

class TestRiverGameModelSuite : public CxxTest::TestSuite
{
    public:
    void testEmptyConstructor() {
       RiverGameModel* test = new RiverGameModel();
       delete test;
    }

};

#endif
