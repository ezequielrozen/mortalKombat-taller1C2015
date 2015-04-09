#include "GameController.h"

GameController::GameController()
{
    mainEvent = new SDL_Event();

    timer = SDL_GetTicks();
}


GameController::~GameController(void)
{
    delete mainEvent;
}

SDL_Event* GameController::getEvent() {
    return mainEvent;
}

void GameController::checkEvent() {
    SDL_PollEvent(mainEvent);    
}

void GameController::update(MKCharacter* character) {
    
    if (mainEvent->type == SDL_KEYDOWN)
    {
        if (mainEvent->key.keysym.sym == SDLK_RIGHT)
        {
            character->setMovement("RIGHT");
            timer = SDL_GetTicks();
            //cout << "right" << endl;
        }
        else if (mainEvent->key.keysym.sym == SDLK_LEFT)
        {
            character->setMovement("LEFT");
            timer = SDL_GetTicks();
            
        }
        else if (mainEvent->key.keysym.sym == SDLK_UP)
		{
            character->setJump(true); 
		}
    }
    else if (timer + COMMANDDELAY < SDL_GetTicks()) {
        
        character->setMovement("NONE");
        timer = SDL_GetTicks();
    }
}



