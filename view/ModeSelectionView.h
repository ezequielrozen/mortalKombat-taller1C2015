#ifndef MODESELECTIONVIEW_H
#define MODESELECTION_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../model/constantes.h"
#include "Text.h"
#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <SDL2/SDL_mixer.h>

using namespace std;

class ModeSelectionView 
{
public:
	ModeSelectionView(SDL_Renderer* aRenderer);
	~ModeSelectionView();
	void render();

private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	int img_width;
	int img_height;

	SDL_Rect draw;
	SDL_Rect crop;
};

#endif // MODESELECTION_H