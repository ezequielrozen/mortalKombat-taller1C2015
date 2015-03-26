/*
 * MKSprite.h
 *
 *  Created on: Mar 24, 2015
 *      Author: gonza
 */

#ifndef MKSPRITE_H_
#define MKSPRITE_H_

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

class MKSprite
{
public:
        MKSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h);

        ~MKSprite(void);

        void DrawSteady();
        void Draw();

        void Walk(int BeginFrame, int EndFrame, float Speed);
        void WalkBack(int BeginFrame, int EndFrame, float Speed);
        void SetUpAnimation(int passed_Amount_X, int passed_Amount_Y);

        int getX();

        void setX(int passedX);
private:

        SDL_Texture* image;
        SDL_Rect rect;

        SDL_Rect crop;

        int img_width;
        int img_height;
        int CurrentFrame;
        int animationDelay;

        int Amount_Frame_X;
        int Amount_Frame_Y;

        SDL_Renderer* renderer;
};

#endif /* MKSPRITE_H_ */
