#include "GameModel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

class Game
{
    GameModel gameModel;
    SDL_Window *window;

    bool map_selected = false;

    void menuScreenLoop();
    void playLoop(bool *outerQuit);
    void gameOverLoop(bool *outerQuit);
    void gameLoopUpdate();

    void mainLoop();
    void setup();
    void update();

    void handleInput(SDL_Event input);

    void handleMouseInput(SDL_Event input);

    SDL_Surface* loadSurface(std::string);

    TTF_Font *mainFont;

    int screenWidth;
    int screenHeight;

    int currentScreen;

    std::string backgroundImagePath;

    SDL_Surface *unselectedUnadjacentHexSurface;
    SDL_Surface *unselectedAdjacentHexSurface;
    SDL_Surface *selectedHexSurface;
    SDL_Surface *attackTargetSurface;

public:
    Game();
    ~Game();
    void start();
};
