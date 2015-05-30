/*
 * EventController.h
 *
 *  Created on: 16/05/2015
 *      Author: her
 */
#ifndef EVENTCONTROLLER_H_
#define EVENTCONTROLLER_H_

#include "SDL2/SDL.h"
#include "../model/constantes.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>
#include <bits/stl_list.h>
#include "../model/MKCharacter.h"
#include "../model/stage/Layer.h"
#include "MKStageController.h"

using namespace std;

class EventController : public MKStageController {


public:
	EventController();
	virtual ~EventController();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void highKick();
	void lowKick();
	void highPunch();
	void lowPunch();
	void shoot();
	void block();
	void duckPunch();

	void moveLeftRelease();
	void moveRightRelease();
	void moveDownRelease();
	void blockRelease();

	void setCharacterToMove(MKCharacter* character);
private:
	static void Void();
	MKCharacter* characterToMove;


};

#endif /* EVENTCONTROLLER_H_ */
