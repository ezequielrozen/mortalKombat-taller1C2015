#ifndef IMAGESPRITE_H
#define IMAGESPRITE_H

#include <iostream>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <SDL2/SDL_image.h>
#include "../../model/util/Util.h"

class ImageSprite
{
public:
	ImageSprite(SDL_Renderer* aRenderer, string path, int x, int y, int w, int h);
	ImageSprite(SDL_Renderer* aRenderer, string path, string alternatepath, int x, int y, int w, int h);
	~ImageSprite();
	void Draw();
    void DrawAlternate();
    void setPosition(int x, int y);
    int getX();
    int getY();
    int getWidth();
    void setWidth(int w);
    int getHieght();
    void setHeight(int h);

private:
	SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Texture* alternateTexture;
    SDL_Rect draw;

    SDL_Rect crop;
    int img_width;
    int img_height;

};

#endif // IMAGESPRITE_H