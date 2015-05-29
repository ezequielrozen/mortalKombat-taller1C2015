#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include "constantes.h"
#include "../controller/InputController.h"
#include "../view/CharacterSelectionView.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <SDL2/SDL_mixer.h>

class CharacterSelection 
{
public:
	CharacterSelection(SDL_Renderer* renderer);
	~CharacterSelection();
	void loop();

private:
	CharacterSelectionView* view;
};

#endif // CHARACTERSELECTION_H