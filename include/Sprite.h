#ifndef SPRITE_H
#define SPRITE_H
#include <string>


class Sprite
{
    std::string path;

    SDL_Surface* loadSprite();

    public:
        Sprite(std::string path);
};

#endif // SPRITE_H
