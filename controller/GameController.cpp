#include "GameController.h"
#include "../model/logger.h"

GameController::GameController()
{
    mainEvent = new SDL_Event();
    joystickController = new JoystickController();
    timer = SDL_GetTicks();
}


GameController::~GameController(void)
{
    delete joystickController;
    delete mainEvent;
}

SDL_Event* GameController::getEvent() {
    return mainEvent;
}

void GameController::checkEvent() {
    SDL_PollEvent(mainEvent);
}

void GameController::update(MKCharacter* character, MKCharacter* character2) {
     extern logger* Mylog;

    this->joystickController->update(character,character2);

    if (mainEvent->type == SDL_KEYDOWN)
    {
        if (mainEvent->key.keysym.sym == SDLK_RIGHT)
        {
            Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
            character->setMovement("RIGHT");
            timer = SDL_GetTicks();
            //cout << "right" << endl;
        } else if (mainEvent->key.keysym.sym == SDLK_d)
        {
            Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
            character2->setMovement("RIGHT");
            timer = SDL_GetTicks();
            //cout << "right" << endl;
        }
        else if (mainEvent->key.keysym.sym == SDLK_LEFT)
        {
            Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
            character->setMovement("LEFT");
            timer = SDL_GetTicks();

        } else if (mainEvent->key.keysym.sym == SDLK_a)
        {
            Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
            character2->setMovement("LEFT");
            timer = SDL_GetTicks();

        }
        else if (mainEvent->key.keysym.sym == SDLK_UP)
		{
        	Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
            character->setJump(true);
		} else if (mainEvent->key.keysym.sym == SDLK_w)
        {
            Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
            character2->setJump(true);
        }
        else if (mainEvent->key.keysym.sym == SDLK_DOWN)
		{
        	Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
            character->setMovement("DUCK");
            timer = SDL_GetTicks();
		} else if (mainEvent->key.keysym.sym == SDLK_s)
        {
            Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
            character2->setMovement("DUCK");
            timer = SDL_GetTicks();
        }
        else if (mainEvent->key.keysym.sym == SDLK_k)
		{
        	Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
            character->setMovement("KICK");
            timer = SDL_GetTicks();
		} else if (mainEvent->key.keysym.sym == SDLK_f)
        {
            Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
            character2->setMovement("KICK");
            timer = SDL_GetTicks();
        }
    }
    else if (timer + COMMANDDELAY < SDL_GetTicks()) {

        character->setMovement("NONE");
        character2->setMovement("NONE");
        timer = SDL_GetTicks();
    }
}



