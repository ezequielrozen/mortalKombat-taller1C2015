#ifndef MKSPRITE_H_
#define MKSPRITE_H_

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../../model/constantes.h"

using namespace std;

class CharacterSprite
{
public:
    CharacterSprite(SDL_Renderer* passed_renderer, char* FilePath, float x, float y, float w, float h, int frames, string OponentSide, bool repearLastSprite);

    ~CharacterSprite(void);
    void Draw();

    void Play(float Speed);
    void PlayBack(float Speed);
    float getX();
    void setX(float passedX);
    void setY(float passedY);
    void reset();
    void switchSide(const char c);
    bool getRepeatLastSprite();
    void setRepeatLastSprite(bool repeat);

private:

    SDL_Texture* texture;
    SDL_Rect draw;

    SDL_Rect crop;

    int img_width;
    int img_height;
    int CurrentFrame;
    int animationDelay;

    int framesX;

    float scalingConstant;

    string oponentSide;

    SDL_Renderer* renderer;

    bool repeatLastSprite;
};

#endif /* MKSPRITE_H_ */
