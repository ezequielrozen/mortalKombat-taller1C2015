#include "KeyboardController.h"
#include "InputController.h"

KeyboardController::KeyboardController(MKStageController* stageController)  {
	this->stageController = stageController;
	for (int i = 0; i < 31; i++) {
		this->keysPressed[i] = false;
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
				if (!keysPressed[0]) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveRight(0);
					this->keysPressed[0] = true;
				}
				break;
			case SDLK_LEFT:
				if (!keysPressed[1]) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveLeft(0);
					this->keysPressed[1] = true;
				}
				break;
			case SDLK_UP:
				if (!keysPressed[2]) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveUp(0);
					this->keysPressed[2] = true;
				}
				break;
			case SDLK_DOWN:
				if (!keysPressed[3]) {
					this->stageController->setCharacterToMove(character);
					this->stageController->moveDown(0);
					this->keysPressed[3] = true;
				}
				break;
			case SDLK_k:
				if (!keysPressed[4]) {
					this->stageController->setCharacterToMove(character);
					this->stageController->highKick(0);
					this->stageController->updateName("K");
					this->keysPressed[4] = true;
				}
				break;
			case SDLK_l:
				if (!keysPressed[5]) {
					this->stageController->setCharacterToMove(character);
					this->stageController->updateName("L");
					this->stageController->lowKick(0);
					this->keysPressed[5] = true;
				}
				break;
			case SDLK_p:
				if (!keysPressed[6]) {
					this->stageController->setCharacterToMove(character);
					this->stageController->highPunch(0);
					this->stageController->updateName("P");
					this->keysPressed[6] = true;
				}
				break;
			case SDLK_i:
				if (!keysPressed[7]) {
					this->stageController->setCharacterToMove(character);
					this->stageController->lowPunch(0);
					this->stageController->updateName("I");
					this->keysPressed[7] = true;
				}
				break;
			case SDLK_b:
				if (!keysPressed[8]) {
					this->stageController->setCharacterToMove(character);
					this->stageController->block(0);
					this->stageController->updateName("B");
					this->keysPressed[8] = true;
				}
				break;
			case SDLK_u:
				if (!keysPressed[9]) {
					this->stageController->setCharacterToMove(character);
					this->stageController->shoot(0);
					this->stageController->updateName("U");
					this->keysPressed[9] = true;
				}
				break;
			case SDLK_o:
				if (!keysPressed[10]) {
					this->stageController->setCharacterToMove(character);
					this->stageController->duckPunch();
					this->stageController->updateName("O");
					this->keysPressed[10] = true;
				}
				break;
			/****************************************************************************************************/

			case SDLK_d:
				if (!keysPressed[11]) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveRight(1);
					this->stageController->updateName("D");
					this->keysPressed[11] = true;
				}
				break;

			case SDLK_a:
				if (!keysPressed[12]) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveLeft(1);
					this->stageController->updateName("A");
					this->keysPressed[12] = true;
				}
				break;
			case SDLK_w:
				if (!keysPressed[13]) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveUp(1);
					this->stageController->updateName("W");
					this->keysPressed[13] = true;
				}
				break;
			case SDLK_z:
				if (!keysPressed[14]) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveDown(1);
					this->stageController->updateName("Z");
					this->keysPressed[14] = true;
				}
				break;

			case SDLK_f:
				if (!keysPressed[15]) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->highKick(1);
					this->stageController->updateName("F");
					this->keysPressed[15] = true;
				}
				break;
			case SDLK_g:
				if (!keysPressed[16]) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->updateName("G");
					this->stageController->lowKick(1);
					this->keysPressed[16] = true;
				}
				break;
			case SDLK_c:
				if (!keysPressed[17]) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->highPunch(1);
					this->stageController->updateName("C");
					this->keysPressed[17] = true;
				}
				break;
			case SDLK_v:
				if (!keysPressed[18]) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->lowPunch(1);
					this->stageController->updateName("V");
					this->keysPressed[18] = true;
				}
				break;
			case SDLK_x:
				if (!keysPressed[19]) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->block(1);
					this->stageController->updateName("X");
					this->keysPressed[19] = true;
				}
				break;

			case SDLK_e:
				if (!keysPressed[20]) {
					this->stageController->setCharacterToMove(character2);
					this->stageController->shoot(1);
					this->stageController->updateName("E");
					this->keysPressed[20] = true;
				}
				break;
			case SDLK_q:
				if (!keysPressed[21]) {
					this->stageController->updateName("Q");
					this->keysPressed[21] = true;
				}
				break;
			case SDLK_r:
				if (!keysPressed[22]) {
					this->stageController->updateName("R");
					this->keysPressed[22] = true;
				}
				break;
			case SDLK_t:
				if (!keysPressed[23]) {
					this->stageController->updateName("T");
					this->keysPressed[23] = true;
				}
				break;
			case SDLK_y:
				if (!keysPressed[24]) {
					this->stageController->updateName("Y");
					this->keysPressed[24] = true;
				}
				break;
			case SDLK_s:
				if (!keysPressed[25]) {
					this->stageController->updateName("S");
					this->keysPressed[25] = true;
				}
				break;
			case SDLK_h:
				if (!keysPressed[26]) {
					this->stageController->updateName("H");
					this->keysPressed[26] = true;
				}
				break;
			case SDLK_j:
				if (!keysPressed[27]) {
					this->stageController->updateName("J");
					this->keysPressed[27] = true;
				}
				break;
			case SDLK_m:
				if (!keysPressed[28]) {
					this->stageController->updateName("M");
					this->keysPressed[28] = true;
				}
				break;
			case SDLK_n:
				if (!keysPressed[29]) {
					this->stageController->updateName("N");
					this->keysPressed[29] = true;
				}
				break;
			case SDLK_BACKSPACE:
				if (!keysPressed[30]) {
					this->stageController->updateName("DEL");
					this->keysPressed[30] = true;
				}
				break;
			case SDLK_RETURN:
				if (!keysPressed[31]) {
					this->stageController->updateName("ENTER");
					this->keysPressed[31] = true;
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
					this->keysPressed[3] = false;
					break;
				case SDLK_RIGHT:
					this->stageController->setCharacterToMove(character);
					this->stageController->moveRightRelease(0);
					this->keysPressed[0] = false;
					break;
				case SDLK_LEFT:
					this->stageController->setCharacterToMove(character);
					this->stageController->moveLeftRelease(0);
					this->keysPressed[1] = false;
					break;
				case SDLK_UP:
					this->stageController->moveUpRelease(0);
					this->keysPressed[2] = false;
					break;
				case SDLK_b:
					this->stageController->setCharacterToMove(character);
					this->stageController->blockRelease(0);
					this->keysPressed[8] = false;
					break;
				case SDLK_k:
					this->stageController->setCharacterToMove(character);
					this->stageController->highKickRelease(0);
					this->keysPressed[4] = false;
					break;
				case SDLK_l:
					this->stageController->setCharacterToMove(character);
					this->stageController->lowKickRelease(0);
					this->keysPressed[5] = false;
					break;
				case SDLK_p:
					this->stageController->setCharacterToMove(character);
					this->stageController->highPunchRelease(0);
					this->keysPressed[6] = false;
					break;
				case SDLK_i:
					this->stageController->setCharacterToMove(character);
					this->stageController->lowPunchRelease(0);
					this->keysPressed[7] = false;
					break;
				case SDLK_u:
					this->stageController->weaponRelease(0);
					this->keysPressed[9] = false;
					break;
				case SDLK_o:
					this->keysPressed[10] = false;
					break;


				case SDLK_z:
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveDownRelease(1);
					this->keysPressed[14] = false;
					break;
				case SDLK_w:
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveUpRelease(1);
					this->keysPressed[13] = false;
					break;
				case SDLK_d:
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveRightRelease(1);
					this->keysPressed[11] = false;
					break;
				case SDLK_a:
					this->stageController->setCharacterToMove(character2);
					this->stageController->moveLeftRelease(1);
					this->keysPressed[12] = false;
					break;
				case SDLK_f:
					this->stageController->setCharacterToMove(character2);
					this->stageController->highKickRelease(1);
					this->keysPressed[15] = false;
					break;
				case SDLK_g:
					this->stageController->setCharacterToMove(character2);
					this->stageController->lowKickRelease(1);
					this->keysPressed[16] = false;
					break;
				case SDLK_c:
					this->stageController->setCharacterToMove(character2);
					this->stageController->highPunchRelease(1);
					this->keysPressed[17] = false;
					break;
				case SDLK_v:
					this->stageController->setCharacterToMove(character2);
					this->stageController->lowPunchRelease(1);
					this->keysPressed[18] = false;
					break;
				case SDLK_x:
					this->stageController->setCharacterToMove(character2);
					this->stageController->blockRelease(1);
					this->keysPressed[19] = false;
					break;
				case SDLK_e:
					this->stageController->weaponRelease(1);
					this->keysPressed[20] = false;
					break;
				case SDLK_q:
					this->keysPressed[21] = false;
					break;
				case SDLK_r:
					this->keysPressed[22] = false;
					break;
				case SDLK_t:
					this->keysPressed[23] = false;
					break;
				case SDLK_y:
					this->keysPressed[24] = false;
					break;
				case SDLK_s:
					this->keysPressed[25] = false;
					break;
				case SDLK_h:
					this->keysPressed[26] = false;
					break;
				case SDLK_j:
					this->keysPressed[27] = false;
					break;
				case SDLK_m:
					this->keysPressed[28] = false;
					break;
				case SDLK_n:
					this->keysPressed[29] = false;
					break;
				case SDLK_BACKSPACE:
					this->keysPressed[30] = false;
					break;
				case SDLK_RETURN:
					this->keysPressed[31] = false;
					break;


				default:
					break;
			}
			break;
    	default:
    		break;
    }
}





