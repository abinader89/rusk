#ifndef GAME_MODEL_CXXTEST_H
#define GAME_MODEL_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "GameModel.h"
#include "PangaeaGameModel.h"
#include "RiverGameModel.h"

class GameModelTestSuite : public CxxTest::TestSuite
{
    public:
        void testHandleSelectionChange() {
            PangaeaGameModel* testPangaeaGM = new PangaeaGameModel();
            TS_ASSERT(testPangaeaGM->board[0].isSelected);
            //up does nothing if top
            testPangaeaGM->handleSelectionChange(0);
            TS_ASSERT(testPangaeaGM->board[0].isSelected);
            //left does nothing if far left
            testPangaeaGM->handleSelectionChange(2);
            TS_ASSERT(testPangaeaGM->board[0].isSelected);
            //right works
            testPangaeaGM->handleSelectionChange(3);
            TS_ASSERT(!testPangaeaGM->board[0].isSelected);
            TS_ASSERT(testPangaeaGM->board[1].isSelected);
            //down works
            testPangaeaGM->handleSelectionChange(1);
            TS_ASSERT(!testPangaeaGM->board[1].isSelected);
            TS_ASSERT(testPangaeaGM->board[8].isSelected);
            //now up works
            testPangaeaGM->handleSelectionChange(0);
            TS_ASSERT(!testPangaeaGM->board[8].isSelected);
            TS_ASSERT(testPangaeaGM->board[1].isSelected);
            //now left works
            testPangaeaGM->handleSelectionChange(2);
            TS_ASSERT(!testPangaeaGM->board[1].isSelected);
            TS_ASSERT(testPangaeaGM->board[0].isSelected);
            delete testPangaeaGM;
        }

        void testNumPlayers() {
            {
                RiverGameModel* test0 = new RiverGameModel();
                TS_ASSERT_EQUALS(test0->numPlayers, 2);
                delete test0;
            }

            {
                PangaeaGameModel* test1 = new PangaeaGameModel();
                TS_ASSERT_EQUALS(test1->numPlayers, 4);
                delete test1;
            }
            {
                //   GameModel testPangaeaGM_;
                //   testPangaeaGM_._()
                //   TS_ASSERT_EQUALS(testPangaeaGM_._(), 3);
            }
        }

        void testProceed() {
            RiverGameModel* test3 = new RiverGameModel(); 
            test3->proceed();

            TS_ASSERT(!(test3->isInReinforcementStage));
            TS_ASSERT_EQUALS(test3->reinforcementsLeft, 0);
            delete test3;
        }

        void testEndAttackMode() {
            PangaeaGameModel* test4 = new PangaeaGameModel();

            test4->endAttackMode();

            TS_ASSERT(!(test4->isInAttackMode));
            delete test4;
        }

};

#endif
