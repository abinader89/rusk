#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "Game.h"

class Sprite
{
    public:
        static SDL_Surface* loadSpriteForPath(std::string path);
    private:
        Sprite();
};

#endif // SPRITE_H
