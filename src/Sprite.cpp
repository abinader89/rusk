#include "Sprite.h"
#include <string>

SDL_Surface* Sprite::loadSpriteForPath(std::string path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    return loadedSurface;
}
