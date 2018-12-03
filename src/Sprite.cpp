#include "Sprite.h"
#include <string>

Sprite::Sprite(std::string path) : path(path) {}

SDL_Surface* Sprite::loadSprite() {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    return loadedSurface;
}
