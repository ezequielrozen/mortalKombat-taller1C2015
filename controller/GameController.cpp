#include "GameController.h"
#include "../model/logger.h"

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

void GameController::update(MKCharacter* character, MKCharacter* character2) {
     extern logger* Mylog;

    if (mainEvent->type == SDL_KEYDOWN)
    {
    	switch(mainEvent->key.keysym.sym){
			case SDLK_RIGHT:
				Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
				character->setMovement("RIGHT");
				timer = SDL_GetTicks();
				break;
			case SDLK_d:
				Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
				character2->setMovement("RIGHT");
				timer = SDL_GetTicks();
				break;
			case SDLK_LEFT:
				Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
				character->setMovement("LEFT");
				timer = SDL_GetTicks();
				break;
			case SDLK_a:
				Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
				character2->setMovement("LEFT");
				timer = SDL_GetTicks();
				break;
			case SDLK_UP:
				Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
				character->setJump(true);
				break;
			case SDLK_w:
				Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
				character2->setJump(true);
				break;
			case SDLK_DOWN:
				Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
				character->setMovement("DUCK");
				timer = SDL_GetTicks();
				break;
			case SDLK_s:
				Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
				character2->setMovement("DUCK");
				timer = SDL_GetTicks();
				break;
			case SDLK_k:
				Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
				character->setMovement("KICK");
				timer = SDL_GetTicks();
				break;
			case SDLK_f:
				Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
				character2->setMovement("KICK");
				timer = SDL_GetTicks();
				break;
			default:
				break;
		}
    }
    else if (timer + COMMANDDELAY < SDL_GetTicks()) {

        character->setMovement("NONE");
        character2->setMovement("NONE");
        timer = SDL_GetTicks();
    }
}



