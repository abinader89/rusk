#ifndef PANGAEA_GAME_MODEL_CXXTEST_H
#define PANGAEA_GAME_MODEL_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "Hex.h"
#include "PangaeaGameModel.h"

class TestPangaeaGameModelSuite : public CxxTest::TestSuite
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
                PangaeaGameModel* testPangaeaGM = new PangaeaGameModel();
                TS_ASSERT_EQUALS(testPangaeaGM->numPlayers, 4);
                delete testPangaeaGM;
            }

            void testProceed() {
                PangaeaGameModel* testPangaeaGM = new PangaeaGameModel(); 
                testPangaeaGM->proceed();

                TS_ASSERT(!(testPangaeaGM->isInReinforcementStage));
                TS_ASSERT_EQUALS(testPangaeaGM->reinforcementsLeft, 0);
                delete testPangaeaGM;
            }

            void testEndAttackMode() {
                PangaeaGameModel* testPangaeaGM = new PangaeaGameModel();
                testPangaeaGM->endAttackMode();

                TS_ASSERT(!(testPangaeaGM->isInAttackMode));
                delete testPangaeaGM;
            }

        };

#endif
