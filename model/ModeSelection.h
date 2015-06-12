#ifndef MODESELECTION_H
#define MODESELECTION_H

#include "constantes.h"
#include "../controller/InputController.h"
#include "../view/ModeSelectionView.h"
#include "util/Button.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <vector>

using namespace std;

class InputController;

class ModeSelection 
{
public:
	ModeSelection(SDL_Renderer* renderer, InputController* inputController);
	~ModeSelection();
	GameModes loop();
	void moveUp();
	void moveDown();
	void select();
	void mouseSelect();
	void linkInputController();
	void updateMousePosition(unsigned short x, unsigned short y);

private:
	ModeSelectionView* view;
	InputController* inputController;
	Button** buttons;
	int peviousKey;
	int index;
	bool selectionMade;
	bool mouseOnButton;
};

#endif // MODESELECTION_H