#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

#include "SDL2/SDL.h"
#include "../model/constantes.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>
#include "MKStageController.h"

using namespace std;

class MouseController 
{
public:
	MouseController(MKStageController* stageController);
	~MouseController();
	void update(SDL_Event* mainEvent);
	void setStageController(MKStageController* stageController);

private:
	MKStageController* stageController;
	bool buttonPressed;
};

#endif // MOUSECONTROLLER_H