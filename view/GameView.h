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
    GameView(float ScreenWidth, float ScreenHeight, MKCharacter* character, Stage* stage);
    ~GameView();
    void Render();
    void LoadSprites();

    void startRender();
    void endRender();

private:

    MKCharacter* scorpion;
    Stage* stage;

    CharacterSprite * scorpionWalk;
    CharacterSprite * scorpionStance;
    CharacterSprite* scorpionJump;
    CharacterSprite* scorpionSideJump;
    LayerSprite* layerSprite;
    LayerSprite* layerSpriteSubway;


    SDL_Window* window;
    SDL_Renderer* renderer;
    float screenWidth;
    float screenHeight;

};

#endif /* GAMEVIEW_H_ */
