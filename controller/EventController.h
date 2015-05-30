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

using namespace std;

class EventController {


public:
	EventController();
	virtual ~EventController();
	void moveRight(MKCharacter*, MKCharacter*);
	void moveLeft(MKCharacter*, MKCharacter*);
	void moveUp(MKCharacter*, MKCharacter*);
	void moveDown(MKCharacter*, MKCharacter*);
	void highKick(MKCharacter*, MKCharacter*);
	void lowKick(MKCharacter*, MKCharacter*);
	void highPunch(MKCharacter*, MKCharacter*);
	void lowPunch(MKCharacter*, MKCharacter*);
	void shoot(MKCharacter*, MKCharacter*);
	void block(MKCharacter*, MKCharacter*);
	void duckPunch(MKCharacter*, MKCharacter*);

	void moveLeftRelease(MKCharacter*, MKCharacter*);
	void moveRightRelease(MKCharacter*, MKCharacter*);
	void moveDownRelease(MKCharacter*, MKCharacter*);
	void blockRelease(MKCharacter*, MKCharacter*);


private:
	static void Void();


};

#endif /* EVENTCONTROLLER_H_ */
