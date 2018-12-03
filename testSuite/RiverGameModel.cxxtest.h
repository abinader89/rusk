#ifndef RIVER_GAME_MODEL_CXXTEST_H
#define RIVER_GAME_MODEL_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "Hex.h"
#include "RiverGameModel.h"

class TestRiverGameModelSuite : public CxxTest::TestSuite
{
    public:

        void testHandleSelectionChange() {
            RiverGameModel* testRiverGM = new RiverGameModel();
            TS_ASSERT(testRiverGM->board[0].isSelected);
            //up does nothing if top
            testRiverGM->handleSelectionChange(0);
            TS_ASSERT(testRiverGM->board[0].isSelected);
            //left does nothing if far left
            testRiverGM->handleSelectionChange(2);
            TS_ASSERT(testRiverGM->board[0].isSelected);
            //right works
            testRiverGM->handleSelectionChange(3);
            TS_ASSERT(!testRiverGM->board[0].isSelected);
            TS_ASSERT(testRiverGM->board[1].isSelected);
            //down works
            testRiverGM->handleSelectionChange(1);
            TS_ASSERT(!testRiverGM->board[1].isSelected);
            TS_ASSERT(testRiverGM->board[8].isSelected);
            //now up works
            testRiverGM->handleSelectionChange(0);
            TS_ASSERT(!testRiverGM->board[8].isSelected);
            TS_ASSERT(testRiverGM->board[1].isSelected);
            //now left works
            testRiverGM->handleSelectionChange(2);
            TS_ASSERT(!testRiverGM->board[1].isSelected);
            TS_ASSERT(testRiverGM->board[0].isSelected);
            delete testRiverGM;
        }

        void testNumPlayers() {
                RiverGameModel* testRiverGM = new RiverGameModel();
                TS_ASSERT_EQUALS(testRiverGM->numPlayers, 2);
                delete testRiverGM;
            }

            void testProceed() {
                RiverGameModel* testRiverGM = new RiverGameModel(); 
                testRiverGM->proceed();

                TS_ASSERT(!(testRiverGM->isInReinforcementStage));
                TS_ASSERT_EQUALS(testRiverGM->reinforcementsLeft, 0);
                delete testRiverGM;
            }

            void testEndAttackMode() {
                RiverGameModel* testRiverGM = new RiverGameModel();
                testRiverGM->endAttackMode();

                TS_ASSERT(!(testRiverGM->isInAttackMode));
                delete testRiverGM;
            }

        };

#endif
