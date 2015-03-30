#include "GameController.h"

GameController::GameController(GameSetup* pGameSetup)
{
    gameSetup = pGameSetup;

    timeCheck = SDL_GetTicks();

    command = "NONE";
}


GameController::~GameController(void)
{
}

string GameController::getCommand() 
{
    //if (timeCheck + 500 < SDL_GetTicks()) {
        if (gameSetup->getMainEvent()->type == SDL_KEYDOWN)
        {
            if (gameSetup->getMainEvent()->key.keysym.sym == SDLK_RIGHT)
            {
                command = "RIGHT";
            }
            else if (gameSetup->getMainEvent()->key.keysym.sym == SDLK_LEFT)
            {
                command = "LEFT";
            }
        }
        else if (gameSetup->getMainEvent()->type == SDL_KEYUP) {
            if (gameSetup->getMainEvent()->key.keysym.sym == SDLK_RIGHT)
            {
                command = "NONE";
            }
            else if (gameSetup->getMainEvent()->key.keysym.sym == SDLK_LEFT)
            {
                command = "NONE";
            }
        }
        //timeCheck = SDL_GetTicks();
    //}
    return command;
}

