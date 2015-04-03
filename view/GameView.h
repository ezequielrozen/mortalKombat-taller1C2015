#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include "../view/character/CharacterSprite.h"
#include "../model/MKCharacter.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../model/stage/Layer.h"
#include "stage/LayerSprite.h"
#include <string>
#include <math.h>

using namespace std;

class GameView
{
public:
    GameView(float ScreenWidth, float ScreenHeight, MKCharacter* character, Layer* layer);
    ~GameView();
    void Render();
    void LoadSprites();

    void startRender();
    void endRender();

private:

    MKCharacter* scorpion;
    Layer* layer;

    CharacterSprite * scorpionWalk;
    CharacterSprite * scorpionStance;
    CharacterSprite* scorpionJump;
    LayerSprite* layerSprite;


    SDL_Window* window;
    SDL_Renderer* renderer;

};

#endif /* GAMEVIEW_H_ */
