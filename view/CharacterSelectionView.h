#ifndef CHARACTERSELECTIONVIEW_H
#define CHARACTERSELECTIONVIEW_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Text.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <SDL2/SDL_mixer.h>
#include "character/CharacterSprite.h"
#include "stage/ImageSprite.h"
#include "stage/LayerSprite.h"
#include "stage/ButtonSprite.h"
#include "../model/util/Button.h"

using namespace std;

class CharacterSelectionView 
{
public:
	CharacterSelectionView(SDL_Renderer* aRenderer, std::vector<Button*> buttons);
	~CharacterSelectionView();
	void render();
private:
	SDL_Renderer* renderer;

	LayerSprite* background;

	ImageSprite* title;

	ImageSprite* characters;

	std::vector<ButtonSprite*> buttonSprites;

	std::vector<CharacterSprite*> characterSprites;

};
#endif // CHARACTERSELECTIONVIEW_H