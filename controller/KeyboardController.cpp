#include "KeyboardController.h"
#include "InputController.h"

KeyboardController::KeyboardController(MKStageController* stageController)  {
	key_u_Released = true;
	key_e_Released = true;
	this->stageController = stageController;

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
				this->stageController->setCharacterToMove(character);
				this->stageController->moveRight(0);
				break;
			case SDLK_LEFT:
				this->stageController->setCharacterToMove(character);
				this->stageController->moveLeft(0);
				break;
			case SDLK_UP:
				this->stageController->setCharacterToMove(character);
				this->stageController->moveUp(0);
				break;
			case SDLK_DOWN:
				this->stageController->setCharacterToMove(character);
				this->stageController->moveDown(0);
				break;
			case SDLK_k:
				this->stageController->setCharacterToMove(character);
				this->stageController->highKick();
				break;
			case SDLK_l:
				this->stageController->setCharacterToMove(character);
				this->stageController->lowKick(0);
				break;
			case SDLK_p:
				this->stageController->setCharacterToMove(character);
				this->stageController->highPunch();
				break;
			case SDLK_i:
				this->stageController->setCharacterToMove(character);
				this->stageController->lowPunch();
				break;
			case SDLK_b:
				this->stageController->setCharacterToMove(character);
				this->stageController->block();
				break;
			case SDLK_u:
				if (key_u_Released) {
					key_u_Released = false;
					this->stageController->setCharacterToMove(character);
					this->stageController->shoot();
				}
				break;
			case SDLK_o:
				this->stageController->setCharacterToMove(character2);
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
					break;
				case SDLK_RIGHT:
					this->stageController->setCharacterToMove(character);
					this->stageController->moveRightRelease(0);
					break;
				case SDLK_LEFT:
					this->stageController->setCharacterToMove(character);
					this->stageController->moveLeftRelease(0);
					break;
				case SDLK_UP:
					this->stageController->moveUpRelease(0);
					break;
				case SDLK_b:
					this->stageController->setCharacterToMove(character);
					this->stageController->blockRelease();
					break;
				case SDLK_u:
					key_u_Released = true;
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





