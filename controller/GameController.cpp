#include "GameController.h"
#include "../model/logger.h"


GameController::GameController()
{
    mainEvent = new SDL_Event();
    this->joystickController = new JoystickController(mainEvent);
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
				case SDLK_g:
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
					if (previousKey == SDLK_UP)
					{
						Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
						character->setJump(true);
					}
					previousKey = mainEvent->key.keysym.sym;
					break;
				case SDLK_w:
					if (previousKey == SDLK_w)
					{
						Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
						character2->setJump(true);
					}
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
				case SDLK_l:
					character2->setLife(character2->getLife()-10);
					character->setLife(character2->getLife()-10);
					previousKey = mainEvent->key.keysym.sym;;
					timer = SDL_GetTicks();
					break;
				case SDLK_k:
					if (previousKey == SDLK_DOWN){
						Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
						character->setHit("KICKDOWN");
						previousKey = SDLK_DOWN;
						hitTimer = SDL_GetTicks();
					}
					else{
						Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
						character->setHit("KICK");
						previousKey = mainEvent->key.keysym.sym;
						hitTimer = SDL_GetTicks();
					}
					break;
				case SDLK_f:
					if (previousKey == SDLK_DOWN){
						Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
						character2->setHit("KICKDOWN");
						previousKey = SDLK_DOWN;
						hitTimer = SDL_GetTicks();
					}
					else{
						Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
						character2->setHit("KICK");
						previousKey = mainEvent->key.keysym.sym;
						hitTimer = SDL_GetTicks();
					}
					break;
				case SDLK_p:
					if (previousKey == SDLK_LEFT){
						character->setHit("PUNCHJUMPLEFT");
						character->setJump(true);
						Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la izquierda.", ERROR_LEVEL_INFO);
						hitTimer = SDL_GetTicks();
					}
					else if (previousKey == SDLK_RIGHT){
						character->setHit("PUNCHJUMPRIGHT");
						character->setJump(true);
						Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la derecha.", ERROR_LEVEL_INFO);
						hitTimer = SDL_GetTicks();
					}
					else{
						Mylog->Log("movimiento del personaje: Golpe de puño.", ERROR_LEVEL_INFO);
						character->setHit("PUNCH");
						previousKey = mainEvent->key.keysym.sym;
						hitTimer = SDL_GetTicks();
						cout << "PUNCH" << endl;
					}
					break;
				case SDLK_o:
						Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
						character->setMovement("SHOOT");
						previousKey = mainEvent->key.keysym.sym;
						timer = SDL_GetTicks();
						break;
				case SDLK_d:
						Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
						character->setMovement("DEFENSE");
						previousKey = mainEvent->key.keysym.sym;
						timer = SDL_GetTicks();
						break;
				case SDLK_q:
						Mylog->Log("movimiento del personaje: Mareado.", ERROR_LEVEL_INFO);
						character->setMovement("DIZZY");
						previousKey = mainEvent->key.keysym.sym;
						timer = SDL_GetTicks();
						break;
				case SDLK_h:
						Mylog->Log("movimiento del personaje: Recibiendo golpe.", ERROR_LEVEL_INFO);
						character->setMovement("BEINGHIT");
						previousKey = mainEvent->key.keysym.sym;
						timer = SDL_GetTicks();
						break;
				case SDLK_e:
						Mylog->Log("movimiento del personaje: Siendo arrojado.", ERROR_LEVEL_INFO);
						character->setMovement("FALLING");
						//HA: Aca tengo q ver si se tiene q mover a izq o a derecha
						character->moveLeft();
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
					previousKey = SDLK_0;
					break;
				case SDLK_UP:
					previousKey = SDLK_0;
					break;
				case SDLK_RIGHT:
					previousKey = SDLK_0;
					break;
				case SDLK_LEFT:
					previousKey = SDLK_0;
					break;
				default:
					break;
			}

    		if (timer + COMMANDDELAY < SDL_GetTicks()) {
				character->setMovement("NONE");
				character2->setMovement("NONE");
				timer = SDL_GetTicks();
    		}
    		if (hitTimer + COMMANDDELAYKIT < SDL_GetTicks()) {
    			character->setHit("NONE");
				character2->setHit("NONE");
				hitTimer = SDL_GetTicks();
    		}
			break;
    	default:
    		if (timer + COMMANDDELAY < SDL_GetTicks()) {
				character->setMovement("NONE");
				character2->setMovement("NONE");
				timer = SDL_GetTicks();
    		}
    		if (hitTimer + COMMANDDELAYKIT < SDL_GetTicks()) {
				character->setHit("NONE");
				character2->setHit("NONE");
				hitTimer = SDL_GetTicks();
			}
    		break;
    }
}



