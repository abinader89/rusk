#include "Game.h"
#include <string>

Game::Game() : hexSprites() {
    screenWidth = 750;
    screenHeight = 700;
    for (int i = 0; i < gameModel.board.size(); ++i)
    {
        SDL_Surface *newHexSurface;
        hexSurfaces.push_back(newHexSurface);
        SDL_Rect newHexSprite;
        hexSprites.push_back(newHexSprite);
    }
    if (TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }
    mainFont = TTF_OpenFont("fonts/font.otf", 16);
}

void Game::start()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
    SDL_SetWindowTitle(window, "RUSK");
    menuScreenLoop();
}

void Game::menuScreenLoop()
{

    bool quit = false;
    while (!quit)
    {
        SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
        SDL_Surface *background_surface  = loadSurface("bmps/menuScreenBackground.bmp");
        SDL_BlitSurface( background_surface, NULL, screenSurface, NULL );
        //Update the surface
        SDL_UpdateWindowSurface(window);
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
                        backgroundImagePath = "bmps/gameScreenBackgroundPangaea.bmp";
                        gameModel = GameModel();
                        gameModel.setupPangaeaGame();
                        playLoop(&quit);
                        break;
                    case SDLK_2:
                        backgroundImagePath = "bmps/gameScreenBackgroundBridge.bmp";
                        gameModel = GameModel();
                        gameModel.setupRiverGame();
                        playLoop(&quit);
                        break;
                    default:
                        break;
                }

            }
        }
    }
}

void Game::gameLoopUpdate()
{
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    SDL_Surface *background_surface  = loadSurface(backgroundImagePath);
    SDL_BlitSurface( background_surface, NULL, screenSurface, NULL );
    SDL_Color black = {0, 0, 0};

    for (int i = 0; i < gameModel.board.size(); ++i)
    {
        if (gameModel.board[i].isSelectable)
        {
            SDL_Color color;
            switch (gameModel.board[i].owner) {
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
                    color = black;
                    break;
                default:
                    break;
            }
            SDL_Rect hexSprite = hexSprites[i];
            SDL_Rect armyCountRect;
            SDL_Surface *hexSurface = hexSurfaces[i];
            std::string hexFileName = "bmps/hex";
            if (gameModel.board[i].isAttackTarget)
            {
                hexFileName += "AttackTarget.bmp";
            }
            else
            {
                hexFileName += gameModel.board[i].isAdjacent && !gameModel.isInReinforcementStage ? "Adjacent" : "Unadjacent";
                hexFileName += gameModel.board[i].isSelected ? "Selected" : "Unselected";
                hexFileName += ".bmp";
            }
            hexSurface = loadSurface(hexFileName);

            hexSprite.x = gameModel.board[i].x;
            hexSprite.y = gameModel.board[i].y;

            armyCountRect.x = hexSprite.x + 45;
            armyCountRect.y = hexSprite.y + 40;
            int count = gameModel.board[i].numberOfArmies;
            std::string count_string = std::to_string(count);

            SDL_Surface* armyCountSurface = TTF_RenderText_Solid(mainFont, count_string.c_str(), color);
            SDL_BlitSurface(hexSurface, NULL, screenSurface, &hexSprite);
            SDL_BlitSurface(armyCountSurface, NULL, screenSurface, &armyCountRect);
            SDL_FreeSurface(hexSurface);
            SDL_FreeSurface(armyCountSurface);
        }
    }

    SDL_Rect currentPlayerTurnRect;
    currentPlayerTurnRect.x = 10;
    currentPlayerTurnRect.y = 30;
    std::string currentPlayerTurnString = "Current Turn: Player " + std::to_string((gameModel.currentTurn % gameModel.numPlayers) + 1);
    SDL_Surface *currentPlayerTurnSurface = TTF_RenderText_Solid(mainFont, currentPlayerTurnString.c_str(), black);
    SDL_BlitSurface(currentPlayerTurnSurface, NULL, screenSurface, &currentPlayerTurnRect);
    SDL_FreeSurface(currentPlayerTurnSurface);

    SDL_Rect currentStageRect;
    currentStageRect.x = 10;
    currentStageRect.y = 50;
    std::string currentStageString = "Current Stage: ";
    currentStageString += gameModel.isInReinforcementStage ? "Reinforcement" : "Attack";
    SDL_Surface *currentStageSurface = TTF_RenderText_Solid(mainFont, currentStageString.c_str(), black);
    SDL_BlitSurface(currentStageSurface, NULL, screenSurface, &currentStageRect);
    SDL_FreeSurface(currentStageSurface);

    SDL_Rect reinforcementsLeftRect;
    reinforcementsLeftRect.x = 10;
    reinforcementsLeftRect.y = 70;
    std::string reinforcementsLeftString = "Reinforcements Left: " + std::to_string(gameModel.reinforcementsLeft);
    SDL_Surface *reinforcementsLeftSurface = TTF_RenderText_Solid(mainFont, reinforcementsLeftString.c_str(), black);
    SDL_BlitSurface(reinforcementsLeftSurface, NULL, screenSurface, &reinforcementsLeftRect);
    SDL_FreeSurface(reinforcementsLeftSurface);



    SDL_UpdateWindowSurface(window);
}

void Game::playLoop(bool *outerQuit)
{
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
                    case SDLK_g:
                        gameModel.proceed();
                        break;
                    case SDLK_SPACE:
                        gameModel.handleSelect();
                        break;
                    case SDLK_ESCAPE:
                        gameModel.endAttackMode();
                        break;
                    default:
                        break;
                }
            }
        }
        gameLoopUpdate();
        if (gameModel.winner != -1)
        {
            gameOverLoop(&quit);
        }
    }
}

void Game::gameOverLoop(bool *outerQuit)
{
    SDL_Color black = {0, 0, 0};
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    SDL_Surface *background_surface  = loadSurface("bmps/gameOverBackground.bmp");
    SDL_BlitSurface(background_surface, NULL, screenSurface, NULL );

    SDL_Rect winnerRect;
    winnerRect.x = screenWidth / 2;
    winnerRect.y = screenHeight / 2;
    std::string winnerString = "Player " + std::to_string(gameModel.winner + 1) + "Wins!";
    SDL_Surface *winnerSurface = TTF_RenderText_Solid(mainFont, winnerString.c_str(), black);
    SDL_BlitSurface(winnerSurface, NULL, screenSurface, &winnerRect);
    SDL_FreeSurface(winnerSurface);

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
                    case SDLK_ESCAPE:
                        quit = true;
                        *outerQuit = true;
                        break;
                    default:
                        break;
                }
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

Game::~Game()
{
    TTF_CloseFont(mainFont);
}
