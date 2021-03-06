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
#include <string>
#include <SDL2/SDL_mixer.h>

struct ButtonInfo {
  int actualButton;
  int lastButton;
  bool buttonPressed;
};

class InputController;

class CharacterSelection 
{
public:
	CharacterSelection(SDL_Renderer* renderer, InputController* inputController);
	~CharacterSelection();
	void loop();
	void linkInputController();
	void moveUp(int n);
	void moveDown(int n);
	void moveRight(int n);
	void moveLeft(int n);
	void select(int n);
	void switchSelected();
	void randomSelection();
	void reset();

	void mouseSelect();
	void updateMousePosition(unsigned short x, unsigned short y);

	void updateName(string letter);

	string getNameOne();
	string getNameTwo();

	void restartNames();

private:
	CharacterSelectionView* view;
	InputController* inputController;

	Button** buttons1;
	Button** buttons2;

	ButtonInfo buttonInfo[2];
	
	Button** nameButtons;
	int nameButtonIndex;

	string names[2];

	bool mouseOnButton;
	bool characterSelectionFinished;
};

#endif // CHARACTERSELECTION_H