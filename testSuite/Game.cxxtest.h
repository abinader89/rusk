#ifndef GAME_CXXTEST_H
#define GAME_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "Game.h"

class GameTestSuite : public CxxTest::TestSuite
{
    public:
        void testLoadSurface() {
            Game* test_game = new Game();
            std::string test_string = "bmps/hexSelected.bmp";
            SDL_Surface* test_surface = test_game->loadSurface(test_string);

            TS_ASSERT_EQUALS(test_surface->w, 100);
            TS_ASSERT_EQUALS(test_surface->h, 100);
            
            SDL_FreeSurface(test_surface); 
        }
};

#endif
