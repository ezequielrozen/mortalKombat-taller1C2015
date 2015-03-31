#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include "../model/MKSprite.h"
#include "../model/GameSetup.h"
#include "../model/MKCharacter.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <math.h>

using namespace std;

class GameView
{
public:
    GameView(GameSetup* pGameSetup, MKCharacter* character);
    ~GameView(void);
    void Draw();
    void LoadSprites();

private:

    MKCharacter* scorpion;

    MKSprite* scorpionWalk;
    MKSprite* scorpionStance;

    int ScreenWidth;
    int ScreenHeight;
    bool quit;
    GameSetup* gameSetup;

};

#endif /* GAMEVIEW_H_ */
