#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "Game.h"

class Sprite
{
    std::string path;


    public:
        Sprite(std::string path);
        SDL_Surface* loadSprite();
};

#endif // SPRITE_H
