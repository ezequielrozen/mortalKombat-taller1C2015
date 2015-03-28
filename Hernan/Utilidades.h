/*
 * Utilidades.h
 *
 *  Created on: 27/03/2015
 *      Author: her
 */

#ifndef UTILIDADES_H_
#define UTILIDADES_H_

#include <string>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Walking animation
const int WALKING_ANIMATION_FRAMES = 9;

//Sprite sheets
const char CAMINANDO_SPRITE_SHEETS[]  = "walking3.png";

class Utilidades {
public:
	Utilidades();
	virtual ~Utilidades();

};

#endif /* UTILIDADES_H_ */
