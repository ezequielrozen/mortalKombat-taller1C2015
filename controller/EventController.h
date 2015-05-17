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
	static void moveRight(MKCharacter*, MKCharacter*);
	static void moveLeft(MKCharacter*, MKCharacter*);
	static void moveUp(MKCharacter*, MKCharacter*);
	static void moveDown(MKCharacter*, MKCharacter*);
	static void highKick(MKCharacter*, MKCharacter*);
	static void lowKick(MKCharacter*, MKCharacter*);
	static void highPunch(MKCharacter*, MKCharacter*);
	static void lowPunch(MKCharacter*, MKCharacter*);
	static void shoot(MKCharacter*, MKCharacter*);
	static void block(MKCharacter*, MKCharacter*);
	static void dizzy(MKCharacter*, MKCharacter*);
	static void beingHit(MKCharacter*, MKCharacter*);
	static void winner(MKCharacter*, MKCharacter*);

	static void setVibrating(bool);

private:



};

#endif /* EVENTCONTROLLER_H_ */
