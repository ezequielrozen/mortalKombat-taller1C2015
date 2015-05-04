#include "GameController.h"
#include "../model/logger.h"

GameController::GameController()
{
    mainEvent = new SDL_Event();
    joystickController = new JoystickController();
    previousKey = 0;

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

//    this->joystickController->update(character,character2);

    switch (mainEvent->type){
    	case SDL_KEYDOWN:
			switch(mainEvent->key.keysym.sym){
				case SDLK_RIGHT:
					Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
					character->setMovement("RIGHT");
					previousKey = mainEvent->key.keysym.sym;
					timer = SDL_GetTicks();
					break;
				case SDLK_d:
					Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
					character2->setMovement("RIGHT");
					previousKey = mainEvent->key.keysym.sym;
					timer = SDL_GetTicks();
					break;
				case SDLK_LEFT:
					Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
					character->setMovement("LEFT");
					previousKey = mainEvent->key.keysym.sym;
					timer = SDL_GetTicks();
					break;
				case SDLK_a:
					Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
					character2->setMovement("LEFT");
					previousKey = mainEvent->key.keysym.sym;
					timer = SDL_GetTicks();
					break;
				case SDLK_UP:
					Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
					character->setJump(true);
					previousKey = mainEvent->key.keysym.sym;
					break;
				case SDLK_w:
					Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
					character2->setJump(true);
					previousKey = mainEvent->key.keysym.sym;
					break;
				case SDLK_DOWN:
					Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
					character->setMovement("DUCK");
					previousKey = mainEvent->key.keysym.sym;
					timer = SDL_GetTicks();
					break;
				case SDLK_s:
					Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
					character2->setMovement("DUCK");
					previousKey = mainEvent->key.keysym.sym;;
					timer = SDL_GetTicks();
					break;
				case SDLK_k:
					if (previousKey == SDLK_DOWN){
						Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
						character->setMovement("KICKDOWN");
						previousKey = SDLK_DOWN;
						timer = SDL_GetTicks();
					}
					else{
						Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
						character->setMovement("KICK");
						previousKey = mainEvent->key.keysym.sym;
						timer = SDL_GetTicks();
					}
					break;
				case SDLK_f:
					Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
					character2->setMovement("KICK");
					previousKey = mainEvent->key.keysym.sym;
					timer = SDL_GetTicks();
					break;
				case SDLK_p:
					Mylog->Log("movimiento del personaje: Golpe de puño.", ERROR_LEVEL_INFO);
					character->setMovement("PUNCH");
					previousKey = mainEvent->key.keysym.sym;
					timer = SDL_GetTicks();
					break;
				default:
					previousKey = mainEvent->key.keysym.sym;
					break;
			}
			break;
		case SDL_KEYUP:
			switch(mainEvent->key.keysym.sym){
				case SDLK_DOWN:
					previousKey = SDLK_k;
					break;
				default:
					break;
			}

    		if (timer + COMMANDDELAY < SDL_GetTicks()) {
				character->setMovement("NONE");
				character2->setMovement("NONE");
				timer = SDL_GetTicks();
    		}
			break;
    	default:
    		if (timer + COMMANDDELAY < SDL_GetTicks()) {
				character->setMovement("NONE");
				character2->setMovement("NONE");
				timer = SDL_GetTicks();
    		}
    		break;
    }
}



