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

void GameController::testElapsedTime(MKCharacter* character,
		MKCharacter* character2) {
	if (timer + COMMANDDELAY < SDL_GetTicks()) {
		character->setMovement("NONE");
		timer = SDL_GetTicks();
	}
	if (hitTimer + COMMANDDELAYKIT < SDL_GetTicks()) {
		character->setHit("NONE");
		hitTimer = SDL_GetTicks();
	}
	if (timerChar2 + COMMANDDELAY < SDL_GetTicks()) {
		character2->setMovement("NONE");
		timerChar2 = SDL_GetTicks();
	}
	if (hitTimerChar2 + COMMANDDELAYKIT < SDL_GetTicks()) {
		character2->setHit("NONE");
		hitTimerChar2 = SDL_GetTicks();
	}
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
				case SDLK_LEFT:
							Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
							character->setMovement("LEFT");
							previousKey = mainEvent->key.keysym.sym;
							timer = SDL_GetTicks();
							break;
				case SDLK_UP:
							if (previousKey == SDLK_UP){
								Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
								character->setJump(true);
							}
							previousKey = mainEvent->key.keysym.sym;
							break;
				case SDLK_DOWN:
							Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
							character->setMovement("DUCK");
							previousKey = mainEvent->key.keysym.sym;
							timer = SDL_GetTicks();
							break;
				case SDLK_l:
							character2->setLife(character2->getLife()-10);
							character->setLife(character->getLife()-10);
							previousKey = mainEvent->key.keysym.sym;
							previousKeyChar2 = mainEvent->key.keysym.sym;
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
							character->setHit("SHOOT");
							previousKey = mainEvent->key.keysym.sym;
							hitTimer = SDL_GetTicks();
							break;
				case SDLK_d:
							Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
							character->setHit("DEFENSE");
							previousKey = mainEvent->key.keysym.sym;
							hitTimer = SDL_GetTicks();
							break;
				case SDLK_q:
							Mylog->Log("movimiento del personaje: Mareado.", ERROR_LEVEL_INFO);
							character->setHit("DIZZY");
							previousKey = mainEvent->key.keysym.sym;
							hitTimer = SDL_GetTicks();
							break;
				case SDLK_h:
							Mylog->Log("movimiento del personaje: Recibiendo golpe.", ERROR_LEVEL_INFO);
							character->setHit("BEINGHIT");
							previousKey = mainEvent->key.keysym.sym;
							hitTimer = SDL_GetTicks();
							break;
				case SDLK_e:
							Mylog->Log("movimiento del personaje: Siendo arrojado.", ERROR_LEVEL_INFO);
							character->setHit("FALLING");
							if(character->getX() > character2->getX()){
								character->moveRight();
							}else{
								character->moveLeft();
							}
							previousKey = mainEvent->key.keysym.sym;
							hitTimer = SDL_GetTicks();
							break;
				case SDLK_y:
							Mylog->Log("movimiento del personaje: Siendo arrojado.", ERROR_LEVEL_INFO);
							character->setHit("WINNER");
							previousKey = mainEvent->key.keysym.sym;
							hitTimer = SDL_GetTicks();
							break;

				/****************************************************************************************************/

				case SDLK_g:
							Mylog->Log("movimiento del personaje: hacia la derecha", ERROR_LEVEL_INFO);
							character2->setMovement("RIGHT");
							previousKeyChar2 = mainEvent->key.keysym.sym;
							timerChar2 = SDL_GetTicks();
							break;
				case SDLK_a:
							Mylog->Log("movimiento del personaje: hacia la izquierda", ERROR_LEVEL_INFO);
							character2->setMovement("LEFT");
							previousKeyChar2 = mainEvent->key.keysym.sym;
							timerChar2 = SDL_GetTicks();
							break;
				case SDLK_w:
							if (previousKeyChar2 == SDLK_w)	{
								Mylog->Log("movimiento del personaje: hacia arriba", ERROR_LEVEL_INFO);
								character2->setJump(true);
							}
							previousKeyChar2 = mainEvent->key.keysym.sym;
							break;
				case SDLK_s:
							Mylog->Log("movimiento del personaje: agachandose", ERROR_LEVEL_INFO);
							character2->setMovement("DUCK");
							previousKeyChar2 = mainEvent->key.keysym.sym;;
							timerChar2 = SDL_GetTicks();
							break;

				case SDLK_f:
							if (previousKeyChar2 == SDLK_s){
								Mylog->Log("movimiento del personaje: Patada baja", ERROR_LEVEL_INFO);
								character2->setHit("KICKDOWN");
								previousKeyChar2 = SDLK_s;
								hitTimerChar2 = SDL_GetTicks();
							}
							else{
								Mylog->Log("movimiento del personaje: Pateando", ERROR_LEVEL_INFO);
								character2->setHit("KICK");
								previousKeyChar2 = mainEvent->key.keysym.sym;
								hitTimerChar2 = SDL_GetTicks();
							}
							break;
				case SDLK_u:
							if (previousKeyChar2 == SDLK_a){
								character2->setHit("PUNCHJUMPLEFT");
								character2->setJump(true);
								Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la izquierda.", ERROR_LEVEL_INFO);
								hitTimerChar2 = SDL_GetTicks();
							}
							else if (previousKeyChar2 == SDLK_g){
								character2->setHit("PUNCHJUMPRIGHT");
								character2->setJump(true);
								Mylog->Log("movimiento del personaje: Golpe de puño con salto hacia la derecha.", ERROR_LEVEL_INFO);
								hitTimerChar2 = SDL_GetTicks();
							}
							else{
								Mylog->Log("movimiento del personaje: Golpe de puño.", ERROR_LEVEL_INFO);
								character2->setHit("PUNCH");
								previousKeyChar2 = mainEvent->key.keysym.sym;
								hitTimerChar2 = SDL_GetTicks();
								cout << "PUNCH" << endl;
							}
							break;
				case SDLK_t:
							Mylog->Log("movimiento del personaje: Disparando.", ERROR_LEVEL_INFO);
							character2->setHit("SHOOT");
							previousKeyChar2 = mainEvent->key.keysym.sym;
							hitTimerChar2 = SDL_GetTicks();
							break;
				case SDLK_n:
							Mylog->Log("movimiento del personaje: Defensa.", ERROR_LEVEL_INFO);
							character2->setHit("DEFENSE");
							previousKeyChar2 = mainEvent->key.keysym.sym;
							hitTimerChar2 = SDL_GetTicks();
							break;
				case SDLK_i:
							Mylog->Log("movimiento del personaje: Mareado.", ERROR_LEVEL_INFO);
							character2->setHit("DIZZY");
							previousKeyChar2 = mainEvent->key.keysym.sym;
							hitTimerChar2 = SDL_GetTicks();
							break;
				case SDLK_b:
							Mylog->Log("movimiento del personaje: Recibiendo golpe.", ERROR_LEVEL_INFO);
							character2->setHit("BEINGHIT");
							previousKeyChar2 = mainEvent->key.keysym.sym;
							hitTimerChar2 = SDL_GetTicks();
							break;
				case SDLK_m:
							Mylog->Log("movimiento del personaje: Siendo arrojado.", ERROR_LEVEL_INFO);
							character2->setHit("FALLING");
							if(character->getX() < character2->getX()){
								character2->moveRight();
							}else{
								character2->moveLeft();
							}
							previousKeyChar2 = mainEvent->key.keysym.sym;
							hitTimerChar2 = SDL_GetTicks();
							break;
				case SDLK_z:
							Mylog->Log("movimiento del personaje: Siendo arrojado.", ERROR_LEVEL_INFO);
							character2->setHit("WINNER");
							previousKeyChar2 = mainEvent->key.keysym.sym;
							hitTimerChar2 = SDL_GetTicks();
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

				case SDLK_s:
					previousKeyChar2 = SDLK_0;
					break;
				case SDLK_w:
					previousKeyChar2 = SDLK_0;
					break;
				case SDLK_g:
					previousKeyChar2 = SDLK_0;
					break;
				case SDLK_a:
					previousKeyChar2 = SDLK_0;
					break;
				default:
					break;
			}
			testElapsedTime(character, character2);
			break;
    	default:
    		testElapsedTime(character, character2);
    		break;
    }
}



