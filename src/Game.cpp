#include "Game.h"

Game::Game() : gameModel(), hexSprites() {
    for (int i = 0; i < gameModel.board.size(); ++i)
    {
        SDL_Surface *newHexSurface;
        hexSurfaces.push_back(newHexSurface);
        SDL_Rect newHexSprite;
        hexSprites.push_back(newHexSprite);
    }
}

void Game::start()
{
    window = SDL_CreateWindow("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 750, 700, 0);
    SDL_SetWindowTitle(window, "RUSK");
    menuScreenLoop();
}

void Game::menuScreenLoop()
{
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    SDL_Surface *background_surface  = loadSurface("bmps/menuScreenBackground.bmp");
    SDL_BlitSurface( background_surface, NULL, screenSurface, NULL );
    //Update the surface
    SDL_UpdateWindowSurface(window);
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }

            if (event.type == SDL_KEYDOWN)
    		{

                switch (event.key.keysym.sym)
    			{
    				case SDLK_1:
                        playLoop(&quit);
                        break;
                }

            }
        }
    }
}

void Game::gameLoopUpdate()
{
    SDL_UpdateWindowSurface(window);
    for (int i = 0; i < gameModel.board.size(); ++i)
    {
        SDL_Rect hexSprite = hexSprites[i];
        SDL_Surface *hexSurface = hexSurfaces[i];
        std::string hexFileName = "bmps/hex";
        hexFileName += gameModel.board[i].isAdjacent ? "Adjacent" : "UnAdjacent";
        hexFileName += gameModel.board[i].isSelected ? "Selected" : "Unselected";
        hexFileName += ".bmp";
        hexSurface = loadSurface(hexFileName);

        hexSprite.x = gameModel.board[i].x;
        hexSprite.y = gameModel.board[i].y;
        SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
        SDL_BlitSurface(hexSurface, NULL, screenSurface, &hexSprite);
        SDL_FreeSurface(hexSurface);
    }
}

void Game::playLoop(bool *outerQuit)
{
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    SDL_Surface *background_surface  = loadSurface("bmps/gameScreenBackground.bmp");
    SDL_BlitSurface( background_surface, NULL, screenSurface, NULL );
    //Update the surface
    SDL_UpdateWindowSurface(window);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                *outerQuit = true;
                break;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        gameModel.handleSelectionChange(0);
                        break;
                    case SDLK_DOWN:
                        gameModel.handleSelectionChange(1);
                        break;
                    case SDLK_LEFT:
                        gameModel.handleSelectionChange(2);
                        break;
                    case SDLK_RIGHT:
                        gameModel.handleSelectionChange(3);
                        break;
                }

            }
        }
        gameLoopUpdate();
    }
}

SDL_Surface* Game::loadSurface(std::string path)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
}
