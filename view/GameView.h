#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include "MKSprite.h"
#include "../model/MKCharacter.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <math.h>

using namespace std;

class GameView
{
public:
    GameView(int ScreenWidth, int ScreenHeight, MKCharacter* character);
    ~GameView(void);
    void Render();
    void LoadSprites();

    void startRender();
    void endRender();

private:

    MKCharacter* scorpion;

    MKSprite* scorpionWalk;
    MKSprite* scorpionStance;

    SDL_Window* window;
    SDL_Renderer* renderer;

};

#endif /* GAMEVIEW_H_ */
