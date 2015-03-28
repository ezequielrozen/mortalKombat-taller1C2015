/*
 * Personaje.h
 *
 *  Created on: 27/03/2015
 *      Author: her
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

class Personaje {
	public:
		//The dimensions of the dot
		static const int PERS_WIDTH = 80;
		static const int PERS_HEIGHT = 200;

		//Maximum axis velocity of the dot
		static const int PERS_VEL = 5;

		//Initializes the variables
		Personaje();

		virtual ~Personaje();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//The X and Y offsets of the dot
		int mPosX, mPosY;

	private:
			//The velocity of the dot
			int mVelX, mVelY;
};
#endif /* PERSONAJE_H_ */
