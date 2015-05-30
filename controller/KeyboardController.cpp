#include "KeyboardController.h"
#include "InputController.h"
#include "EventController.h"

KeyboardController::KeyboardController()  {
	key_u_Released = true;
	key_e_Released = true;
	this->eventController = new EventController();

}

KeyboardController::~KeyboardController(void) {
	delete this->eventController;
}


//void KeyboardController::testElapsedTime(MKCharacter* character, MKCharacter* character2) {
//}


void KeyboardController::update(MKCharacter* character, MKCharacter* character2, SDL_Event* mainEvent) {

    switch (mainEvent->type){
    	case SDL_KEYDOWN:
			switch(mainEvent->key.keysym.sym) {
			case SDLK_RIGHT:
						this->eventController->moveRight(character, character2);
						break;
			case SDLK_LEFT:
						this->eventController->moveLeft(character, character2);
						break;
			case SDLK_UP:
						this->eventController->moveUp(character, character2);
						break;
			case SDLK_DOWN:
						this->eventController->moveDown(character, character2);
						break;
			case SDLK_k:
						this->eventController->highKick(character, character2);
						break;
			case SDLK_l:
						this->eventController->lowKick(character, character2);
						break;
			case SDLK_p:
						this->eventController->highPunch(character, character2);
						break;
			case SDLK_i:
						this->eventController->lowPunch(character, character2);
						break;
			case SDLK_b:
						this->eventController->block(character, character2);
						break;
			case SDLK_u:
						if (key_u_Released)
						{
							key_u_Released = false;
							this->eventController->shoot(character, character2);
						}
						break;
			/****************************************************************************************************/

			case SDLK_d:
						this->eventController->moveRight(character2, character);
						break;

			case SDLK_a:
						this->eventController->moveLeft(character2, character);
						break;
			case SDLK_w:
						this->eventController->moveUp(character2, character);
						break;
			case SDLK_z:
						this->eventController->moveDown(character2, character);
						break;

			case SDLK_f:
						this->eventController->highKick(character2, character);
						break;
			case SDLK_g:
						this->eventController->lowKick(character2, character);
						break;
			case SDLK_c:
						this->eventController->highPunch(character2, character);
						break;
			case SDLK_v:
						this->eventController->lowPunch(character2, character);
						break;
			case SDLK_x:
						this->eventController->block(character2, character);
						break;

			case SDLK_e:
						if (key_e_Released)
						{
							key_e_Released = false;
							this->eventController->shoot(character2, character);
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
					this->eventController->moveDownRelease(character, character2);
					break;
				case SDLK_RIGHT:
					this->eventController->moveRightRelease(character, character2);
					break;
				case SDLK_LEFT:
					this->eventController->moveLeftRelease(character, character2);
					break;
				case SDLK_b:
					this->eventController->blockRelease(character, character2);
					break;
				case SDLK_u:
					key_u_Released = true;
					break;


				case SDLK_z:
					this->eventController->moveDownRelease(character2, character);
					break;
				case SDLK_d:
					this->eventController->moveRightRelease(character2, character);
					break;
				case SDLK_a:
					this->eventController->moveLeftRelease(character2, character);
					break;
				case SDLK_x:
					this->eventController->blockRelease(character2, character);
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





