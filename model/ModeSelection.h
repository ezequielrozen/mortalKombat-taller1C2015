#ifndef MODESELECTION_H
#define MODESELECTION_H

#include "constantes.h"
#include "../controller/InputController.h"
#include "../view/ModeSelectionView.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <SDL2/SDL_mixer.h>

using namespace std;

class ModeSelection 
{
public:
	ModeSelection(SDL_Renderer* renderer, InputController* inputController);
	~ModeSelection();
	void loop();

private:
	ModeSelectionView* view;
	InputController* inputController;
};

#endif // MODESELECTION_H