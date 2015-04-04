#ifndef MKSPRITE_H_
#define MKSPRITE_H_

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;

class CharacterSprite
{
public:
    CharacterSprite(SDL_Renderer* passed_renderer, string FilePath, int x, int y, int w, int h, int frames, string OponentSide);

    ~CharacterSprite(void);
    void Draw();

    void Play(float Speed);
    void PlayBack(float Speed);
    int getX();
    void setX(int passedX);
    void setY(int passedY);
    void reset();

private:

    SDL_Texture* texture;
    SDL_Rect draw;

    SDL_Rect crop;

    int img_width;
    int img_height;
    int CurrentFrame;
    int animationDelay;

    int framesX;

    string oponentSide;

    SDL_Renderer* renderer;
};

#endif /* MKSPRITE_H_ */
