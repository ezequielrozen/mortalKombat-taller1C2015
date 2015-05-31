#ifndef BUTTON_H
#define BUTTON_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <SDL2/SDL_mixer.h>

using namespace std;

class Button 
{
public:
	Button(string aName, bool isSelected);
	~Button();
	bool isSelected();
	void setSelected(bool);
	string getName();
private:
	bool selected;
	string name;
};

#endif // BUTTON_H