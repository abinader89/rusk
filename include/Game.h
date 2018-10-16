#include "GameModel.h"
#include <SDL2/SDL.h>

class Game
{
    GameModel gameModel;
    SDL_Window *window;

    void menuScreenLoop();
    void playLoop();
    SDL_Surface* loadSurface(std::string);

public:
    Game();
    void start();
};
