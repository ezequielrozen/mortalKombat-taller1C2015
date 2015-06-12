#ifndef BUTTONSPRITE_H
#define BUTTONSPRITE_H

#include <iostream>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <SDL2/SDL_image.h>
#include "../../model/util/Util.h"
#include "../../model/util/Button.h"
#include "ImageSprite.h"

class ButtonSprite 
{
public:
	ButtonSprite(SDL_Renderer* aRenderer, Button* aButton);
	~ButtonSprite();
	void Draw();
	bool isSelected();
private:
	SDL_Renderer* renderer;
	Button* button;
    ImageSprite* selectedSprite;
    ImageSprite* notSelectedSprite;
};

#endif // BUTTONSPRITE_H