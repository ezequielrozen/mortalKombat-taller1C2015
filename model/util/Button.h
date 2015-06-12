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
	Button(string aName, bool isSelected, int x, int y, int w, int h);
	~Button();
	bool isSelected();
	void setSelected(bool);
	string getName();
	
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	bool checkBoundaries(unsigned short x, unsigned short y);
private:
	bool selected;
	string name;
	int x;
	int y;
	int w;
	int h;
};

#endif // BUTTON_H