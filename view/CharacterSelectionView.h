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
	CharacterSelectionView(SDL_Renderer* aRenderer, Button** buttons1, Button** buttons2, Button** nameButtons);
	~CharacterSelectionView();
	void render();
	void updateCharacterNames(string name1, string name2);
private:
	SDL_Renderer* renderer;

	LayerSprite* background;

	ImageSprite* title;

	ImageSprite* characters;

	ButtonSprite* buttonSprites1[12];
	ButtonSprite* buttonSprites2[12];
	CharacterSprite* characterSprites1[12];
	CharacterSprite* characterSprites2[12];

	ButtonSprite* nameButtonSprites[2];
	Text* characterNames[2];

};
#endif // CHARACTERSELECTIONVIEW_H