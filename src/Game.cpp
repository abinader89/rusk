#include "Game.h"

Game::Game() : gameModel() {}

void Game::start()
{
    window = SDL_CreateWindow("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
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
                        playLoop();
                        break;
                }

            }
        }
    }
}

void Game::playLoop()
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
            if(event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
        }
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
