#include "Game.h"

#include <iostream>


Game::Game() : gameModel() {}

void Game::start()
{
    std::cout << "Starting game" << std::endl;
    window = SDL_CreateWindow("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);


    loop();
}

void Game::loop()
{
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
