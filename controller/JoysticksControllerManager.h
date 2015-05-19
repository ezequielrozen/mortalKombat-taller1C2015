/*
 * JoysticksControllerManager.h
 *
 *  Created on: 19/05/2015
 *      Author: her
 */

#ifndef JOYSTICKSCONTROLLERMANAGER_H_
#define JOYSTICKSCONTROLLERMANAGER_H_
#include <iostream>
#include "../model/MKCharacter.h"
#include "../model/util/Util.h"
#include "JoystickController.h"

using namespace std;

class JoysticksControllerManager {
public:
	JoysticksControllerManager();
	virtual ~JoysticksControllerManager();
	void update(MKCharacter* character, MKCharacter* character2, SDL_Event* joystickEvent);
	SDL_Event* getEvent();
private:
	SDL_Joystick* joystickOne;
	SDL_Joystick* joystickTwo;

	JoystickController* joystick0;
	JoystickController* joystick1;
	int joystickCount;
};
#endif
