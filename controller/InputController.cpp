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
	this->iaIsActive = false;
	this->keyboardController = new KeyboardController(stageController);
	this->aiController = new AIController(stageController);
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
	delete this->aiController;
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
	//if (!this->iaIsActive) {
		this->keyboardController->update(character, character2, this->getEvent());
	//}

	//if (joystickConnected && !this->iaIsActive) {
		this->joystickControllerManager->update(character, character2, this->getEvent());
	//}

	if (this->iaIsActive) {
		this->aiController->update(character, character2, this->getEvent());
	}
}

void InputController::setStageController(MKStageController *stageController) {
	this->stageController = stageController;
	this->keyboardController->setStageController(stageController);
	this->aiController->setStageController(stageController);
	if (joystickConnected) {
		this->joystickControllerManager->setStageController(stageController);
	}
}

void InputController::setCharacters(MKCharacter *character, MKCharacter *character2) {
	this->character = character;
	this->character2 = character2;
}

void InputController::enableAI() {
	this->iaIsActive = true;
	if (joystickConnected)
		this->joystickControllerManager->enableAI();
}

void InputController::setModeSelection(ModeSelection *modeSelection) {
	this->stageController->setModeSelection(modeSelection);
}

void InputController::setCharacterSelection(CharacterSelection* characterSelection) {
	this->stageController->setCharacterSelection(characterSelection);	
}

void InputController::disableAI() {
	this->iaIsActive = false;
}

void InputController::enablePracticeAI() {
	this->enableAI();
	this->aiController->enablePracticeAI();
}
