#ifndef MODESELECTIONVIEW_H
#define MODESELECTION_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../model/constantes.h"
#include "stage/LayerSprite.h"
#include "stage/ImageSprite.h"
#include "stage/ButtonSprite.h"
#include "../model/util/Button.h"
#include "Text.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <SDL2/SDL_mixer.h>

using namespace std;

class ModeSelectionView 
{
public:
	ModeSelectionView(SDL_Renderer* aRenderer, std::vector<Button*> buttons);
	~ModeSelectionView();
	void render();

private:
	SDL_Renderer* renderer;

	LayerSprite* background;

	ImageSprite* logo;

	ButtonSprite* button1;

	ButtonSprite* button2;

	ButtonSprite* button3;

};

#endif // MODESELECTION_H