#ifndef PANGAEA_GAME_MODEL_CXXTEST_H
#define PANGAEA_GAME_MODEL_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "Hex.h"
#include "PangaeaGameModel.h"

class TestPangaeaGameModelSuite : public CxxTest::TestSuite
{
    public:
    void testEmptyConstructor() {
       PangaeaGameModel* test = new PangaeaGameModel();
       delete test;
    }

};

#endif
