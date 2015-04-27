#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include "../view/character/CharacterSprite.h"
#include "../model/MKCharacter.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../model/stage/Layer.h"
#include "stage/LayerSprite.h"
#include "../model/stage/Stage.h"
#include <string>
#include <math.h>

using namespace std;

class GameView
{
public:
    GameView(float ScreenWidth, float ScreenHeight, MKCharacter* character, MKCharacter* character2, Stage* stage, string OponentSide);
    ~GameView();
    void Render();
    void LoadSprites();

    void startRender();
    void endRender();

private:

    MKCharacter* scorpion;
    MKCharacter* raiden;
    Stage* stage;

    CharacterSprite * scorpionWalk;
    CharacterSprite * scorpionStance;
    CharacterSprite* scorpionJump;
    CharacterSprite* scorpionSideJump;
    CharacterSprite * raidenWalk;
    CharacterSprite * raidenStance;
    CharacterSprite* raidenJump;
    CharacterSprite* raidenSideJump;
    //list<LayerSprite*>* layerSprites = new list<LayerSprite*>();
    LayerSprite** layerSprites;
    int layerCount;

    SDL_Window* window;
    SDL_Renderer* renderer;
    float screenWidth;
    float screenHeight;
    string oponentSide;

    void runCharacter();
};

#endif /* GAMEVIEW_H_ */
