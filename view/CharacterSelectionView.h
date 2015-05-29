#ifndef CHARACTERSELECTIONVIEW_H
#define CHARACTERSELECTIONVIEW_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Text.h"
#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <SDL2/SDL_mixer.h>

using namespace std;

class CharacterSelectionView 
{
public:
	CharacterSelectionView(SDL_Renderer* aRenderer);
	~CharacterSelectionView();
	void render();
private:
	SDL_Renderer* renderer;
};

#endif // CHARACTERSELECTIONVIEW_H