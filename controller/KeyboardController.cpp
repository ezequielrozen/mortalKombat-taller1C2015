#include "KeyboardController.h"
#include "InputController.h"

KeyboardController::KeyboardController(MKStageController* stageController)  {
	key_u_Released = true;
	key_e_Released = true;
	this->stageController = stageController;
	for (int i = 0; i < 2; i++) {
		this->commands[i].downPressed = false;
		this->commands[i].upPressed = false;
		this->commands[i].rightPressed = false;
		this->commands[i].leftPressed = false;
		this->commands[i].highPunchPressed = false;
		this->commands[i].lowPunchPressed = false;
		this->commands[i].highKickPressed = false;
		this->commands[i].lowKickPressed = false;
		this->commands[i].blockPressed = false;
		this->commands[i].weaponThrowPressed = false;
	}
}

KeyboardController::~KeyboardController(void) {
}

void KeyboardController::setStageController(MKStageController* stageController) {
	this->stageController = stageController;
}


void KeyboardController::update(MKCharacter* character, MKCharacter* character2, SDL_Event* mainEvent) {

    switch (mainEvent->type){
    	case SDL_KEYDOWN:
			switch(mainEvent->key.keysym.sym) {
			case SDLK_RIGHT:
				if (!commands[0].rightPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveRight(0);
					this->commands[0].rightPressed = true;
				}
				break;
			case SDLK_LEFT:
				if (!commands[0].leftPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveLeft(0);
					this->commands[0].leftPressed = true;
				}
				break;
			case SDLK_UP:
				if (!commands[0].upPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveUp(0);
					this->commands[0].upPressed = true;
				}
				break;
			case SDLK_DOWN:
				if (!commands[0].downPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveDown(0);
					this->commands[0].downPressed = true;
				}
				break;
			case SDLK_k:
				if (!commands[0].highKickPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->highKick(0);
					this->commands[0].highKickPressed = true;
				}
				break;
			case SDLK_l:
				if (!commands[0].lowKickPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->lowKick(0);
					this->commands[0].lowKickPressed = true;
				}
				break;
			case SDLK_p:
				if (!commands[0].highPunchPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->highPunch(0);
					this->commands[0].highPunchPressed = true;
				}
				break;
			case SDLK_i:
				if (!commands[0].lowPunchPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->lowPunch(0);
					this->commands[0].lowPunchPressed = true;
				}
				break;
			case SDLK_b:
				if (!commands[0].blockPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->block(0);
					this->commands[0].blockPressed = true;
				}
				break;
			case SDLK_u:
				if (key_u_Released) {
					key_u_Released = false;
					this->stageController->setCharacterToMove(character);
					this->stageController->shoot(0);
				}
				break;
			case SDLK_o:
				this->stageController->setCharacterToMove(character);
				this->stageController->duckPunch();
				break;
			/****************************************************************************************************/

			case SDLK_d:
				if (!commands[1].rightPressed) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveRight(1);
					this->commands[1].rightPressed = true;
				}
				break;

			case SDLK_a:
				if (!commands[1].leftPressed) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveLeft(1);
					this->commands[1].leftPressed = true;
				}
				break;
			case SDLK_w:
				if (!commands[1].upPressed) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveUp(1);
					this->commands[1].upPressed = true;
				}
				break;
			case SDLK_z:
				if (!commands[1].downPressed) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveDown(1);
					this->commands[1].downPressed = true;
				}
				break;

			case SDLK_f:
				if (!commands[1].highKickPressed) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->highKick(1);
					this->commands[1].highKickPressed = true;
				}
				break;
			case SDLK_g:
				if (!commands[1].lowKickPressed) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->lowKick(1);
					this->commands[1].lowKickPressed = true;
				}
				break;
			case SDLK_c:
				if (!commands[1].highPunchPressed) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->highPunch(1);
					this->commands[1].highPunchPressed = true;
				}
				break;
			case SDLK_v:
				if (!commands[1].lowPunchPressed) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->lowPunch(1);
					this->commands[1].lowPunchPressed = true;
				}
				break;
			case SDLK_x:
				if (!commands[1].blockPressed) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->block(1);
					this->commands[1].blockPressed = true;
				}
				break;

			case SDLK_e:
				if (key_e_Released) {
					key_e_Released = false;
					this->stageController->setCharacterToMove(character2);
					this->stageController->shoot(1);
				}
				break;
			default:
//				previousKey = mainEvent->key.keysym.sym;
				break;
			}
		break;

		case SDL_KEYUP:
			switch(mainEvent->key.keysym.sym){
				case SDLK_DOWN:
					this->stageController->setCharacterToMove(character);
					this->stageController->moveDownRelease(0);
					this->commands[0].downPressed = false;
					break;
				case SDLK_RIGHT:
					this->stageController->setCharacterToMove(character);
					this->stageController->moveRightRelease(0);
					this->commands[0].rightPressed = false;
					break;
				case SDLK_LEFT:
					this->stageController->setCharacterToMove(character);
					this->stageController->moveLeftRelease(0);
					this->commands[0].leftPressed = false;
					break;
				case SDLK_UP:
					this->stageController->moveUpRelease(0);
					this->commands[0].upPressed = false;
					break;
				case SDLK_b:
					this->stageController->setCharacterToMove(character);
					this->stageController->blockRelease(0);
					this->commands[0].blockPressed = false;
					break;
				case SDLK_k:
					this->stageController->setCharacterToMove(character);
					this->stageController->highKickRelease(0);
					this->commands[0].highKickPressed = false;
					break;
				case SDLK_l:
					this->stageController->setCharacterToMove(character);
					this->stageController->lowKickRelease(0);
					this->commands[0].lowKickPressed = false;
					break;
				case SDLK_p:
					this->stageController->setCharacterToMove(character);
					this->stageController->highPunchRelease(0);
					this->commands[0].highPunchPressed = false;
					break;
				case SDLK_i:
					this->stageController->setCharacterToMove(character);
					this->stageController->lowPunchRelease(0);
					this->commands[0].lowPunchPressed = false;
					break;
				case SDLK_u:
					key_u_Released = true;
					this->stageController->weaponRelease(0);
					break;


				case SDLK_z:
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveDownRelease(1);
					this->commands[1].downPressed = false;
					break;
				case SDLK_w:
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveUpRelease(1);
					this->commands[1].upPressed = false;
					break;
				case SDLK_d:
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveRightRelease(1);
					this->commands[1].rightPressed = false;
					break;
				case SDLK_a:
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveLeftRelease(1);
					this->commands[1].leftPressed = false;
					break;
				case SDLK_f:
					this->stageController->setCharacterToMove(character2);
					this->stageController->highKickRelease(1);
					this->commands[1].highKickPressed = false;
					break;
				case SDLK_g:
					this->stageController->setCharacterToMove(character2);
					this->stageController->lowKickRelease(1);
					this->commands[1].lowKickPressed = false;
					break;
				case SDLK_c:
					this->stageController->setCharacterToMove(character2);
					this->stageController->highPunchRelease(1);
					this->commands[1].highPunchPressed = false;
					break;
				case SDLK_v:
					this->stageController->setCharacterToMove(character2);
					this->stageController->lowPunchRelease(1);
					this->commands[1].lowPunchPressed = false;
					break;
				case SDLK_x:
					this->stageController->setCharacterToMove(character2);
					this->stageController->blockRelease(1);
					this->commands[1].lowPunchPressed = false;
					break;
				case SDLK_e:
					key_e_Released = true;
					this->stageController->weaponRelease(1);
					break;

				default:
					break;
			}
			break;
    	default:
    		break;
    }
}





