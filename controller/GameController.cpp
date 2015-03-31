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
                timeCheck = SDL_GetTicks();
                //right = true;
            }
            else if (gameSetup->getMainEvent()->key.keysym.sym == SDLK_LEFT)
            {
                command = "LEFT";
                timeCheck = SDL_GetTicks();
                //left = true;
            }
        }
	//El timeCheck se ajusta para evitar delay en el cambio de movimiento del personaje. Depende del teclado y la maquina de cada uno.
        else if (timeCheck + 500 < SDL_GetTicks()) {
            command = "NONE";
            timeCheck = SDL_GetTicks();
        }
        //timeCheck = SDL_GetTicks();
    //}
    return command;
}




