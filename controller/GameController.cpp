#include "GameController.h"

GameController::GameController()
{
    mainEvent = new SDL_Event();

    timeCheck = SDL_GetTicks();

    command = "NONE";

}


GameController::~GameController(void)
{
    delete mainEvent;
}

string GameController::getCommand() 
{
    //if (timeCheck + 500 < SDL_GetTicks()) {
        if (mainEvent->type == SDL_KEYDOWN)
        {
            if (mainEvent->key.keysym.sym == SDLK_RIGHT)
            {
                command = "RIGHT";
                timeCheck = SDL_GetTicks();
                //right = true;
            }
            else if (mainEvent->key.keysym.sym == SDLK_LEFT)
            {
                command = "LEFT";
                timeCheck = SDL_GetTicks();
                //left = true;
            }
        }
        else if (timeCheck + 500 < SDL_GetTicks()) {
            command = "NONE";
            timeCheck = SDL_GetTicks();
        }
        //timeCheck = SDL_GetTicks();
    //}
    return command;
}

SDL_Event* GameController::getEvent() {
    return mainEvent;
}

void GameController::checkEvent() {
    SDL_PollEvent(mainEvent);    
}




