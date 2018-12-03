#ifndef SPRITE_CXXTEST_H
#define SPRITE_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "Sprite.h"

class TestSprite : public CxxTest::TestSuite
{
    public:
    void testLoadSprite() {
        Sprite test_sprite = Sprite("sprites/OneSoldier.png");
        SDL_Surface* test_surface = test_sprite.loadSprite();

        TS_ASSERT_EQUALS(test_surface->h, 35);
        TS_ASSERT_EQUALS(test_surface->w, 48);
    }

};

#endif
