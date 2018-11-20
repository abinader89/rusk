#include "Game.h"
#include <string>

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
    SDL_Init(SDL_INIT_VIDEO);
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
        SDL_Color color;
        int current_player = gameModel.board[i].owner.player_number;
        switch (current_player) {
            case 0:
            // red (player 1)
            color = {255, 0, 0};
            break;
            case 1:
            // blue (player 2)
            color = {0, 0, 255};
            break;
            case 2:
            // purple (player 3)
            color = {128, 0, 128};
            break;
            case 3:
            // black (unowned)
            color = {0, 0, 0};
            break;
        }
        SDL_Rect hexSprite = hexSprites[i];
        SDL_Rect font_rect;
        SDL_Surface *hexSurface = hexSurfaces[i];
        std::string hexFileName = "bmps/hex";
        hexFileName += gameModel.board[i].isSelected ? "Selected" : "Unselected";
        hexFileName += ".bmp";
        hexSurface = loadSurface(hexFileName);

        hexSprite.x = gameModel.board[i].x;
        hexSprite.y = gameModel.board[i].y;
        
        font_rect.x = hexSprite.x + 45;
        font_rect.y = hexSprite.y + 40;
        if (TTF_Init() == -1)
        {
            printf("TTF_Init: %s\n", TTF_GetError());
            exit(1);
        }
        TTF_Font* armyCountFont = NULL;
        armyCountFont = TTF_OpenFont("fonts/armalite_rifle.ttf", 16);
        if (!armyCountFont)
        {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
        }
        int count = gameModel.board[i].numberOfArmies;
        std::string count_string = std::to_string(count);
        SDL_Surface* armyCount = TTF_RenderText_Solid(armyCountFont, count_string.c_str(), color);
        if (!armyCount)
        {
            printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
        }

        SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
        SDL_BlitSurface(hexSurface, NULL, screenSurface, &hexSprite);
        SDL_BlitSurface(armyCount, NULL, screenSurface, &font_rect);
        SDL_FreeSurface(hexSurface);
        SDL_FreeSurface(armyCount);
        TTF_CloseFont(armyCountFont);
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
