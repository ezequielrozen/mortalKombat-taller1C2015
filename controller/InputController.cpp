/*
 * InputController.cpp
 *
 *  Created on: 16/05/2015
 *      Author: her
 */

#include "InputController.h"
bool InputController::vibrating = false;

InputController::InputController() {
	this->mainEvent = new SDL_Event();
	this->keyboardController = new KeyboardController();

	SDL_Init(SDL_INIT_JOYSTICK);
	joystickConnected = false;
	if (SDL_NumJoysticks() > 0)	{
		this->joystickController = new JoystickController();
		joystickConnected = true;
	}

}

InputController::~InputController() {
    if (joystickConnected)
    	delete joystickController;
    delete mainEvent;
}

SDL_Event* InputController::getEvent() {
    return mainEvent;
}

void InputController::checkEvent() {
    SDL_PollEvent(mainEvent);
}

void InputController::victory(MKCharacter* character, MKCharacter* character2 ) {
	if (character->isAlive() && !character2->isAlive()) { // Ganó el 1. Loguear
		character->setHit("WINNER");
		character2->setHit("DIZZY");
		//Esto deberia estar aca sino en el MKCharacter setHit. Lo arreglo rapido para la entrega.
		if (character->getName() == "raiden")
			character->setHitWidth(character->getWidth()*1.5);

	} else if (!character->isAlive() && character2->isAlive()) { // Ganó el 2. Loguear.
		character->setHit("DIZZY");
		character2->setHit("WINNER");

		//Esto deberia estar aca sino en el MKCharacter setHit. Lo arreglo rapido para la entrega.
		if (character2->getName() == "raiden")
			character2->setHitWidth(character2->getWidth()*1.5);
	}
}

void InputController::setVibrating(bool vibratingFlag) {
	vibrating = vibratingFlag;
}

bool InputController::isVibrating() {
	return vibrating;
}

void setCharacterSide(MKCharacter* character, MKCharacter* character2)
{
    if(character->getX() <= character2->getX()){
    	character->setCharacterSide('l');
    	character2->setCharacterSide('r');
    }else{
    	character->setCharacterSide('r');
    	character2->setCharacterSide('l');
    }
}

void InputController::update(MKCharacter* character, MKCharacter* character2) {

	this->keyboardController->update(character, character2, this->getEvent());

	if(joystickConnected)
	{
		this->joystickController->update(character, character2, this->getEvent());
	}
}

