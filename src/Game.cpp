#include "Game.h"
#include "PangaeaGameModel.h"
#include "RiverGameModel.h"
#include "RingGameModel.h"
#include "Sprite.h"
#include <string>
#include <iostream>

Game::Game()
{
    screenWidth = 750;
    screenHeight = 700;
}

void Game::start()
{
    if (TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }
    mainFont = TTF_OpenFont("fonts/font.otf", 16);
    unselectedUnadjacentHexSurface = Sprite::loadSpriteForPath("bmps/hexUnadjacentUnselected.bmp");
    unselectedAdjacentHexSurface = Sprite::loadSpriteForPath("bmps/hexAdjacentUnselected.bmp");
    selectedHexSurface = Sprite::loadSpriteForPath("bmps/hexSelected.bmp");
    attackTargetSurface = Sprite::loadSpriteForPath("bmps/hexAttackTarget.bmp");
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
    SDL_SetWindowTitle(window, "RUSK");
    currentScreen = 0;
    mainLoop();
}

void Game::mainLoop()
{
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_WaitEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                handleMouseInput(event);
            }
            if (event.type == SDL_KEYDOWN)
            {
                handleInput(event);
            }
            update();
            SDL_UpdateWindowSurface(window);
        }
    }
}

void Game::update()
{
    if (currentScreen == 0)
    {
        SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
        SDL_Surface *background_surface  = loadSurface("bmps/menuScreenBackground.bmp");

        SDL_BlitSurface( background_surface, NULL, screenSurface, NULL );
        //Update the surface
        SDL_FreeSurface(screenSurface);
        SDL_FreeSurface(background_surface);
    }

    if (currentScreen == 1)
    {
        gameLoopUpdate();
        if (gameModel->winner != -1)
        {
            currentScreen = 2;
        }
    }

    if (currentScreen == 2)
    {
        SDL_Color black = {0, 0, 0};
        SDL_Surface *background_surface  = loadSurface("bmps/gameOverBackground.bmp");
        SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
        SDL_BlitSurface(background_surface, NULL, screenSurface, NULL );
        SDL_FreeSurface(background_surface);

        SDL_Rect winnerRect;
        winnerRect.x = screenWidth / 2;
        winnerRect.y = screenHeight / 2;
        std::string winnerString = "Player " + std::to_string(gameModel->winner + 1) + "Wins!";
        SDL_Surface *winnerSurface = TTF_RenderText_Solid(mainFont, winnerString.c_str(), black);
        SDL_BlitSurface(winnerSurface, NULL, screenSurface, &winnerRect);
        SDL_FreeSurface(winnerSurface);
        SDL_FreeSurface(screenSurface);
    }
}

void Game::handleMouseInput(SDL_Event e)
{
    if (map_selected)
    {
        return;
    }
    Uint32 mouse_input = e.button.button;
    int mouseX = e.motion.x;
    int mouseY = e.motion.y;
    switch (mouse_input)
    {
        case SDL_BUTTON_LEFT:
            if (mouseX > 500
                && mouseX < 700
                && mouseY > 585
                && mouseY < 685)
            {

                backgroundImagePath = "bmps/gameScreenBackgroundPangaea.bmp";
                if (!firstTime)
                {
                    delete gameModel;
                }
                firstTime = false;
                gameModel = new PangaeaGameModel();
                currentScreen = 1;
            }
            else if (mouseX > 50
            && mouseX < 250
            && mouseY > 585
            && mouseY < 685)
            {

                backgroundImagePath = "bmps/gameScreenBackgroundBridge.bmp";
                if (!firstTime)
                {
                    delete gameModel;
                }
                firstTime = false;
                gameModel = new RiverGameModel();
                currentScreen = 1;
            }
            else if (mouseX > 275
                && mouseX < 480
                && mouseY > 585
                && mouseY < 685)
            {
                backgroundImagePath = "bmps/gameScreenBackgroundPangaea.bmp";
                if (!firstTime)
                {
                    delete gameModel;
                }
                firstTime = false;
                gameModel = new RingGameModel();
                currentScreen = 1;
            }
            break;
        default:
            break;
    }
}

void Game::handleInput(SDL_Event e)
{
    size_t key_input = e.key.keysym.sym;
    if (currentScreen == 1)
    {
        switch (key_input)
        {
            case SDLK_UP:
                gameModel->handleSelectionChange(0);
                break;
            case SDLK_DOWN:
                gameModel->handleSelectionChange(1);
                break;
            case SDLK_LEFT:
                gameModel->handleSelectionChange(2);
                break;
            case SDLK_RIGHT:
                gameModel->handleSelectionChange(3);
                break;
            case SDLK_g:
                gameModel->proceed();
                break;
            case SDLK_SPACE:
                gameModel->handleSelect();
                break;
            case SDLK_ESCAPE:
                gameModel->endAttackMode();
                break;
            default:
                break;
        }
    }
    if (currentScreen == 2)
    {
        switch (key_input)
        {
            case SDLK_ESCAPE:
                currentScreen = 0;
                break;
            default:
                break;
        }
    }
}

void Game::gameLoopUpdate()
{
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    SDL_Surface *background_surface  = loadSurface(backgroundImagePath);
    SDL_BlitSurface(background_surface, NULL, screenSurface, NULL);
    SDL_FreeSurface(background_surface);
    SDL_Color black = {0, 0, 0};
    SDL_Color white = {255, 255, 255};

    for (int i = 0; i < gameModel->board.size(); ++i)
    {
        if (gameModel->board[i].isSelectable)
        {
            SDL_Color color;
            switch (gameModel->board[i].owner) {
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
                    color = {255, 0, 255};
                    break;
                case 3:
                    // green (player 4)
                    color = {0, 255, 0};
                    break;
                case -1:
                    // black (unowned)
                    color = white;
                    break;
                default:
                    break;
            }

            SDL_Rect hexSprite;
            SDL_Rect armyCountRect;

            hexSprite.x = gameModel->board[i].x;
            hexSprite.y = gameModel->board[i].y;

            armyCountRect.x = hexSprite.x + 45;
            armyCountRect.y = hexSprite.y + 40;
            int count = gameModel->board[i].numberOfArmies;
            std::string count_string = std::to_string(count);

            SDL_Surface* armyCountSurface = TTF_RenderText_Shaded(mainFont, count_string.c_str(), black, color);
            if (gameModel->board[i].isAttackTarget)
            {
                SDL_BlitSurface(attackTargetSurface, NULL, screenSurface, &hexSprite);
            }
            else if (gameModel->board[i].isSelected)
            {
                SDL_BlitSurface(selectedHexSurface, NULL, screenSurface, &hexSprite);
            }
            else if (gameModel->board[i].isAdjacent && !gameModel->isInReinforcementStage)
            {
                SDL_BlitSurface(unselectedAdjacentHexSurface, NULL, screenSurface, &hexSprite);
            }
            else
            {
                SDL_BlitSurface(unselectedUnadjacentHexSurface, NULL, screenSurface, &hexSprite);
            }
            SDL_BlitSurface(armyCountSurface, NULL, screenSurface, &armyCountRect);
            SDL_FreeSurface(armyCountSurface);
            SDL_FreeSurface(screenSurface);
        }
    }

    SDL_Rect currentPlayerTurnRect;
    currentPlayerTurnRect.x = 10;
    currentPlayerTurnRect.y = 30;
    std::string currentPlayerTurnString = "Current Turn: Player " + std::to_string((gameModel->currentTurn % gameModel->numPlayers) + 1);
    SDL_Surface *currentPlayerTurnSurface = TTF_RenderText_Solid(mainFont, currentPlayerTurnString.c_str(), black);
    SDL_BlitSurface(currentPlayerTurnSurface, NULL, screenSurface, &currentPlayerTurnRect);
    SDL_FreeSurface(currentPlayerTurnSurface);

    SDL_Rect currentStageRect;
    currentStageRect.x = 10;
    currentStageRect.y = 50;
    std::string currentStageString = "Current Stage: ";
    currentStageString += gameModel->isInReinforcementStage ? "Reinforcement" : "Attack";
    SDL_Surface *currentStageSurface = TTF_RenderText_Solid(mainFont, currentStageString.c_str(), black);
    SDL_BlitSurface(currentStageSurface, NULL, screenSurface, &currentStageRect);
    SDL_FreeSurface(currentStageSurface);

    SDL_Rect reinforcementsLeftRect;
    reinforcementsLeftRect.x = 10;
    reinforcementsLeftRect.y = 70;
    std::string reinforcementsLeftString = "Reinforcements Left: " + std::to_string(gameModel->reinforcementsLeft);
    SDL_Surface *reinforcementsLeftSurface = TTF_RenderText_Solid(mainFont, reinforcementsLeftString.c_str(), black);
    SDL_BlitSurface(reinforcementsLeftSurface, NULL, screenSurface, &reinforcementsLeftRect);
    SDL_FreeSurface(reinforcementsLeftSurface);
}

SDL_Surface* Game::loadSurface(std::string path)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL)
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
}

Game::~Game()
{
    TTF_CloseFont(mainFont);
    SDL_FreeSurface(unselectedUnadjacentHexSurface);
    SDL_FreeSurface(unselectedAdjacentHexSurface);
    SDL_FreeSurface(selectedHexSurface);
    SDL_FreeSurface(attackTargetSurface);
    delete gameModel;
}
