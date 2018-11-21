#include "GameModel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

class Game
{
    GameModel gameModel;
    SDL_Window *window;
    std::vector<SDL_Surface *> hexSurfaces;
    std::vector<SDL_Rect> hexSprites;

    void menuScreenLoop();
    void playLoop(bool *outerQuit);
    void gameOverLoop(bool *outerQuit);
    void gameLoopUpdate();
    SDL_Surface* loadSurface(std::string);

    TTF_Font *mainFont;

    int screenWidth;
    int screenHeight;

    std::string backgroundImagePath;

public:
    Game();
    ~Game();
    void start();
};
