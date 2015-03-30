#ifndef GAME_H_
#define GAME_H_

#include "GameSetup.h"
#include "MKSprite.h"
#include "MKCharacter.h"
#include "../view/GameView.h"
#include "../controller/GameController.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <math.h>

const int INITIAL_POSITION_X = 200;
const int INITIAL_POSITION_Y = 200;

class Game
{
public:
    Game(int pScreenWidth, int pScreenHeight);
    ~Game(void);
    void GameLoop();

private:

    MKCharacter* scorpion;

    int ScreenWidth;
    int ScreenHeight;
    bool quit;
    GameSetup* gameSetup;
    GameView* gameView;
    GameController* gameController;

};

#endif /* GAME_H_ */
