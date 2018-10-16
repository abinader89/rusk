#include "GameModel.h"
#include <SDL2/SDL.h>

class Game
{
    GameModel gameModel;
    SDL_Window *window;

    void loop();

public:
    Game();
    void start();
};
