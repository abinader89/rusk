#include "GameModel.h"
#include <SDL2/SDL.h>

class Game
{
    GameModel gameModel;
    SDL_Window *window;
    std::vector<SDL_Surface *> hexSurfaces;
    std::vector<SDL_Rect> hexSprites;

    void menuScreenLoop();
    void playLoop(bool *outerQuit);
    void gameLoopUpdate();
    SDL_Surface* loadSurface(std::string);

public:
    Game();
    void start();
};
