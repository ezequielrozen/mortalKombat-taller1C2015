#include "KeyboardController.h"
#include "InputController.h"
#include "EventController.h"

KeyboardController::KeyboardController()
{
	key_u_Released = true;
	key_e_Released = true;
}

KeyboardController::~KeyboardController(void)
{
}


void KeyboardController::testElapsedTime(MKCharacter* character, MKCharacter* character2) {
}


void KeyboardController::update(MKCharacter* character, MKCharacter* character2, SDL_Event* mainEvent) {

    switch (mainEvent->type){
    	case SDL_KEYDOWN:
			switch(mainEvent->key.keysym.sym) {
			case SDLK_RIGHT:
						EventController::moveRight(character, character2);
						break;
			case SDLK_LEFT:
						EventController::moveLeft(character, character2);
						break;
			case SDLK_UP:
						EventController::moveUp(character, character2);
						break;
			case SDLK_DOWN:
						EventController::moveDown(character, character2);
						break;
			case SDLK_k:
						EventController::highKick(character, character2);
						break;
			case SDLK_l:
						EventController::lowKick(character, character2);
						break;
			case SDLK_p:
						EventController::highPunch(character, character2);
						break;
			case SDLK_i:
						EventController::lowPunch(character, character2);
						break;
			case SDLK_b:
						EventController::block(character, character2);
						break;
			case SDLK_u:
						if (key_u_Released)
						{
							key_u_Released = false;
							EventController::shoot(character, character2);
						}
						break;
			/****************************************************************************************************/

			case SDLK_d:
						EventController::moveRight(character2, character);
						break;

			case SDLK_a:
						EventController::moveLeft(character2, character);
						break;
			case SDLK_w:
						EventController::moveUp(character2, character);
						break;
			case SDLK_z:
						EventController::moveDown(character2, character);
						break;

			case SDLK_f:
						EventController::highKick(character2, character);
						break;
			case SDLK_g:
						EventController::lowKick(character2, character);
						break;
			case SDLK_c:
						EventController::highPunch(character2, character);
						break;
			case SDLK_v:
						EventController::lowPunch(character2, character);
						break;
			case SDLK_x:
						EventController::block(character2, character);
						break;

			case SDLK_e:
						if (key_e_Released)
						{
							key_e_Released = false;
							EventController::shoot(character2, character);
						}
						break;
			default:
				previousKey = mainEvent->key.keysym.sym;
				break;
			}
		break;

		case SDL_KEYUP:
			switch(mainEvent->key.keysym.sym){
				case SDLK_DOWN:
					EventController::moveDownRelease(character, character2);
					break;
				case SDLK_RIGHT:
					EventController::moveRightRelease(character, character2);
					break;
				case SDLK_LEFT:
					EventController::moveLeftRelease(character, character2);
					break;
				case SDLK_b:
					EventController::blockRelease(character, character2);
					break;
				case SDLK_u:
					key_u_Released = true;
					break;


				case SDLK_z:
					EventController::moveDownRelease(character2, character);
					break;
				case SDLK_d:
					EventController::moveRightRelease(character2, character);
					break;
				case SDLK_a:
					EventController::moveLeftRelease(character2, character);
					break;
				case SDLK_x:
					EventController::blockRelease(character2, character);
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





