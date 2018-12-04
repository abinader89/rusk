#ifndef SPRITE_CXXTEST_H
#define SPRITE_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "Sprite.h"

class TestSprite : public CxxTest::TestSuite
{
    public:
    void testLoadSprite() {
        SDL_Surface *testSurface = Sprite::loadSpriteForPath("sprites/OneSoldier.png");

        TS_ASSERT_EQUALS(testSurface->h, 35);
        TS_ASSERT_EQUALS(testSurface->w, 48);

        SDL_FreeSurface(testSurface);
    }
};

#endif
