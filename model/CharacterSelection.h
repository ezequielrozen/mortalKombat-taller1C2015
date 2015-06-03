#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include "constantes.h"
#include "../controller/InputController.h"
#include "../view/CharacterSelectionView.h"
#include "util/Button.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>
#include <SDL2/SDL_mixer.h>

class InputController;

class CharacterSelection 
{
public:
	CharacterSelection(SDL_Renderer* renderer, InputController* inputController);
	~CharacterSelection();
	void loop();
	void linkInputController();
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

private:
	CharacterSelectionView* view;
	InputController* inputController;
	std::vector<Button*> buttons;
};

#endif // CHARACTERSELECTION_H