#include "KeyboardController.h"
#include "InputController.h"

KeyboardController::KeyboardController(MKStageController* stageController)  {
	key_u_Released = true;
	key_e_Released = true;
	this->stageController = stageController;
	this->downPressed = false;
	this->upPressed = false;
	this->rightPressed = false;
	this->leftPressed = false;
	this->highPunchPressed = false;
	this->lowPunchPressed = false;
	this->highKickPressed = false;
	this->lowKickPressed = false;
	this->blockPressed = false;
	this->weaponThrowPressed = false;
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
				if (!rightPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveRight(0);
					this->rightPressed = true;
				}
				break;
			case SDLK_LEFT:
				if (!leftPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveLeft(0);
					this->leftPressed = true;
				}
				break;
			case SDLK_UP:
				if (!upPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveUp(0);
					this->upPressed = true;
				}
				break;
			case SDLK_DOWN:
				if (!downPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveDown(0);
					this->downPressed = true;
				}
				break;
			case SDLK_k:
				if (!highKickPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->highKick();
					this->highKickPressed = true;
				}
				break;
			case SDLK_l:
				if (!lowKickPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->lowKick(0);
					this->lowKickPressed = true;
				}
				break;
			case SDLK_p:
				if (!highPunchPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->highPunch();
					this->highPunchPressed = true;
				}
				break;
			case SDLK_i:
				if (!lowPunchPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->lowPunch();
					this->lowPunchPressed = true;
				}
				break;
			case SDLK_b:
				if (!blockPressed) {
					this->stageController->setCharacterToMove(character);
					this->stageController->block();
					this->blockPressed = true;
				}
				break;
			case SDLK_u:
				if (key_u_Released) {
					key_u_Released = false;
					this->stageController->setCharacterToMove(character);
					this->stageController->shoot();
				}
				break;
			case SDLK_o:
				this->stageController->setCharacterToMove(character);
				this->stageController->duckPunch();
				break;
			/****************************************************************************************************/

			case SDLK_d:
				this->stageController->setCharacterToMove(character2);
				this->stageController->moveRight(1);
				break;

			case SDLK_a:
				this->stageController->setCharacterToMove(character2);
				this->stageController->moveLeft(1);
				break;
			case SDLK_w:
				this->stageController->setCharacterToMove(character2);
				this->stageController->moveUp(1);
				break;
			case SDLK_z:
				this->stageController->setCharacterToMove(character2);
				this->stageController->moveDown(1);
				break;

			case SDLK_f:
				this->stageController->setCharacterToMove(character2);
				this->stageController->highKick();
				break;
			case SDLK_g:
				this->stageController->setCharacterToMove(character2);
				this->stageController->lowKick(1);
				break;
			case SDLK_c:
				this->stageController->setCharacterToMove(character2);
				this->stageController->highPunch();
				break;
			case SDLK_v:
				this->stageController->setCharacterToMove(character2);
				this->stageController->lowPunch();
				break;
			case SDLK_x:
				this->stageController->setCharacterToMove(character2);
				this->stageController->block();
				break;

			case SDLK_e:
				if (key_e_Released) {
					key_e_Released = false;
					this->stageController->setCharacterToMove(character2);
					this->stageController->shoot();
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
					this->downPressed = false;
					break;
				case SDLK_RIGHT:
					this->stageController->setCharacterToMove(character);
					this->stageController->moveRightRelease(0);
					this->rightPressed = false;
					break;
				case SDLK_LEFT:
					this->stageController->setCharacterToMove(character);
					this->stageController->moveLeftRelease(0);
					this->leftPressed = false;
					break;
				case SDLK_UP:
					this->stageController->moveUpRelease(0);
					this->upPressed = false;
					break;
				case SDLK_b:
					this->stageController->setCharacterToMove(character);
					this->stageController->blockRelease();
					this->blockPressed = false;
					break;
				case SDLK_k:
					this->stageController->setCharacterToMove(character);
					this->stageController->highKickRelease(0);
					this->highKickPressed = false;
				case SDLK_l:
					this->stageController->setCharacterToMove(character);
					this->stageController->lowKickRelease(0);
					this->lowKickPressed = false;
				case SDLK_p:
					this->stageController->setCharacterToMove(character);
					this->stageController->highPunchRelease(0);
					this->highPunchPressed = false;
				case SDLK_i:
					this->stageController->setCharacterToMove(character);
					this->stageController->lowPunchRelease(0);
					this->lowPunchPressed = false;
				case SDLK_u:
					key_u_Released = true;
					this->stageController->weaponRelease();
					break;


				case SDLK_z:
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveDownRelease(1);
					break;
				case SDLK_w:
					this->stageController->moveUpRelease(1);
					break;
				case SDLK_d:
					this->stageController->moveRightRelease(1);
					break;
				case SDLK_a:
					this->stageController->moveLeftRelease(1);
					break;
				case SDLK_x:
					this->stageController->blockRelease();
					break;
				case SDLK_e:
					key_e_Released = true;
					break;

				default:
					break;
			}
			break;
    	default:
    		break;
    }
}





