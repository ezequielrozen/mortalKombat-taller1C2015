/*
 * GameSetup.h
 *
 *  Created on: Mar 24, 2015
 *      Author: gonza
 */

#ifndef GAMESETUP_H_
#define GAMESETUP_H_

#include "SDL2/SDL.h"

class GameSetup {
public:
	GameSetup(bool* quit, int ScreenWidth, int ScreenHeight);
	virtual ~GameSetup();
	SDL_Renderer* getRenderer();
	SDL_Event* getMainEvent();
	void Begin();
	void End();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* mainEvent;
};

#endif /* GAMESETUP_H_ */
