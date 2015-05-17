/*
 * InputController.h
 *
 *  Created on: 16/05/2015
 *      Author: her
 */

#ifndef INPUTCONTROLLER_H_
#define INPUTCONTROLLER_H_

#include "SDL2/SDL.h"
#include "KeyboardController.h"
#include "JoystickController.h"
#include "../model/constantes.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>
#include <bits/stl_list.h>
#include "../model/MKCharacter.h"
#include "../model/stage/Layer.h"

class KeyboardController;
class InputController {
public:
	InputController();
	virtual ~InputController();
	void update(MKCharacter* character, MKCharacter* character2);
	void checkEvent();
	SDL_Event* getEvent();

	void victory(MKCharacter* character, MKCharacter* character2);
	static void setVibrating(bool vibratingFlag);
	static bool isVibrating();
private:
	JoystickController* joystickController;
	KeyboardController* keyboardController;
    SDL_Event* mainEvent;
    bool joystickConnected;
    static bool vibrating;
};
	void setCharacterSide(MKCharacter* character, MKCharacter* character2);
#endif
