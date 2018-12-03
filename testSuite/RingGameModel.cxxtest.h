#ifndef RING_GAME_MODEL_CXXTEST_H
#define RING_GAME_MODEL_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "Hex.h"
#include "RingGameModel.h"

class TestRingGameModelSuite : public CxxTest::TestSuite
{
    public:

        void testHandleSelectionChange() {
            RingGameModel* testRingGM = new RingGameModel();
            TS_ASSERT(testRingGM->board[0].isSelected);
            //up does nothing if top
            testRingGM->handleSelectionChange(0);
            TS_ASSERT(testRingGM->board[0].isSelected);
            //left does nothing if far left
            testRingGM->handleSelectionChange(2);
            TS_ASSERT(testRingGM->board[0].isSelected);
            //right works
            testRingGM->handleSelectionChange(3);
            TS_ASSERT(!testRingGM->board[0].isSelected);
            TS_ASSERT(testRingGM->board[1].isSelected);
            //down works
            testRingGM->handleSelectionChange(1);
            TS_ASSERT(!testRingGM->board[1].isSelected);
            TS_ASSERT(testRingGM->board[8].isSelected);
            //now up works
            testRingGM->handleSelectionChange(0);
            TS_ASSERT(!testRingGM->board[8].isSelected);
            TS_ASSERT(testRingGM->board[1].isSelected);
            //now left works
            testRingGM->handleSelectionChange(2);
            TS_ASSERT(!testRingGM->board[1].isSelected);
            TS_ASSERT(testRingGM->board[0].isSelected);
            delete testRingGM;
        }

        void testNumPlayers() {
                RingGameModel* testRingGM = new RingGameModel();
                TS_ASSERT_EQUALS(testRingGM->numPlayers, 3);
                delete testRingGM;
            }

            void testProceed() {
                RingGameModel* testRingGM = new RingGameModel(); 
                testRingGM->proceed();

                TS_ASSERT(!(testRingGM->isInReinforcementStage));
                TS_ASSERT_EQUALS(testRingGM->reinforcementsLeft, 0);
                delete testRingGM;
            }

            void testEndAttackMode() {
                RingGameModel* testRingGM = new RingGameModel();
                testRingGM->endAttackMode();

                TS_ASSERT(!(testRingGM->isInAttackMode));
                delete testRingGM;
            }

        };

#endif
