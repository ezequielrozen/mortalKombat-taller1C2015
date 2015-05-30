/*
 * InputController.cpp
 *
 *  Created on: 16/05/2015
 *      Author: her
 */

#include "InputController.h"
bool InputController::vibrating = false;

InputController::InputController(MKStageController* stageController) {
	this->mainEvent = new SDL_Event();
	this->stageController = stageController;

	this->keyboardController = new KeyboardController(stageController);
	SDL_Init(SDL_INIT_JOYSTICK);
	joystickConnected = false;
	if (SDL_NumJoysticks() > 0)	{
		this->joystickControllerManager = new JoysticksControllerManager(stageController);
		joystickConnected = true;
	}

}

InputController::~InputController() {
    if (joystickConnected)
    	delete joystickControllerManager;
    delete mainEvent;
    delete this->keyboardController;
}

SDL_Event* InputController::getEvent() {
    return mainEvent;
}

void InputController::checkEvent() {
    SDL_PollEvent(mainEvent);
}

void InputController::setVibrating(bool vibratingFlag) {
	vibrating = vibratingFlag;
}

bool InputController::isVibrating() {
	return vibrating;
}

void InputController::setCharacterSide()
{
    if(character->getX() <= character2->getX()){
    	character->setCharacterSide('l');
    	character2->setCharacterSide('r');
    }else{
    	character->setCharacterSide('r');
    	character2->setCharacterSide('l');
    }
}

void InputController::update() {

	this->setCharacterSide();

	this->keyboardController->update(character, character2, this->getEvent());

	if(joystickConnected)
	{
		this->joystickControllerManager->update(character, character2, this->getEvent());
	}
}

void InputController::setStageController(MKStageController *stageController) {
	this->stageController = stageController;
}

void InputController::setCharacters(MKCharacter *character, MKCharacter *character2) {
	this->character = character;
	this->character2 = character2;
}
