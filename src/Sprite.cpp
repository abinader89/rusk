#include "Sprite.h"
#include <string>

Sprite::Sprite(string path)
{
    path(path);
}

Sprite::SDL_Surface* loadSprite() {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    return loadedSurface;
}
