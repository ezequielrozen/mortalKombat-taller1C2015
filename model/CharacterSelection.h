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


private:
	CharacterSelectionView* view;
	InputController* inputController;
	std::vector<Button*> buttons1;
	std::vector<Button*> buttons2;

	std::vector<ButtonInfo> buttonInfo;

};

#endif // CHARACTERSELECTION_H