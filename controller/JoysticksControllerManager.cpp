/*
 * JoysticksControllerManager.cpp
 *
 *  Created on: 19/05/2015
 *      Author: her
 */

#include "JoysticksControllerManager.h"
#include "JoystickController.h"
#include "InputController.h"
#include "EventController.h"

JoysticksControllerManager::JoysticksControllerManager(MKStageController* stageController) {
	joystickOne = NULL;
	joystickTwo = NULL;
	extern logger* Mylog;

	char mensaje[100];
	sprintf(mensaje, "Joysticks conectados: %d", SDL_NumJoysticks());
	Mylog->Log(mensaje, ERROR_LEVEL_INFO);
    this->stageController = stageController;

    switch (SDL_NumJoysticks()) {
        case 1:
            this->joystickOne = SDL_JoystickOpen(0);
            Mylog->Log(SDL_JoystickName(joystickOne), ERROR_LEVEL_INFO);
            cout << SDL_JoystickName(joystickOne) << endl;
            joystick0 = new JoystickController(0, stageController);
            joystickCount = 1;
            SDL_JoystickEventState(SDL_ENABLE);
            break;
        case 2:
            this->joystickOne = SDL_JoystickOpen(0);
            this->joystickTwo = SDL_JoystickOpen(1);
            Mylog->Log(SDL_JoystickName(joystickOne), ERROR_LEVEL_INFO);
            Mylog->Log(SDL_JoystickName(joystickTwo), ERROR_LEVEL_INFO);
            cout << SDL_JoystickName(joystickOne) << endl;
            cout << SDL_JoystickName(joystickTwo) << endl;

            joystick0 = new JoystickController(0, stageController);
            joystick1 = new JoystickController(1, stageController);
            joystickCount = 2;
            SDL_JoystickEventState(SDL_ENABLE);
            break;
        default:
            Mylog->Log("No se detectaron los joysticks", ERROR_LEVEL_WARNING);
            joystickCount = 0;
            break;
    }

}

JoysticksControllerManager::~JoysticksControllerManager() {
	if (joystickCount == 1){
		delete joystick0;
	}
	if (joystickCount == 2){
		delete joystick0;
		delete joystick1;
	}
}

void JoysticksControllerManager::setStageController(MKStageController* stageController) {
    this->stageController = stageController;
    this->joystick0->setStageController(stageController);
    this->joystick1->setStageController(stageController);    
}

void JoysticksControllerManager::update(MKCharacter *character, MKCharacter *character2, SDL_Event* mainEvent) {
    extern logger *Mylog;
    char mensaje[100];
//    SDL_PollEvent(mainEvent);

    unsigned char pressedJoystick = mainEvent->jbutton.which;
    unsigned char pressedButton = mainEvent->jbutton.button;
    unsigned  char pressedAxis = mainEvent->jaxis.axis;
    int pressedAxisValue = mainEvent->jaxis.value;

    bool printCout = false;

    if (mainEvent->type == SDL_JOYBUTTONDOWN || mainEvent->type == SDL_JOYAXISMOTION  || mainEvent->type == SDL_JOYBUTTONUP) {
        sprintf(mensaje, "JOYSTICK %d BUTTON PRESSED: %d", (int) pressedJoystick, (int) pressedButton);
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
    }else{	return;	}

	switch(pressedJoystick){
	case 0:
		this->stageController->setCharacterToMove(character);
        this->joystick0->update(character, character2, mainEvent);
		break;
	case 1:
        this->stageController->setCharacterToMove(character2);
		this->joystick1->update(character2, character, mainEvent);
		break;
	}
}


