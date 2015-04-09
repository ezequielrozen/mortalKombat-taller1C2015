#ifndef GAME_H
#define GAME_H

#include "MKCharacter.h"
#include "../view/GameView.h"
#include "../controller/GameController.h"
#include "../controller/CameraController.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "stage/Stage.h"
#include <math.h>
#include <iostream>

using namespace std;

const int INITIAL_POSITION_X = 200;
const int INITIAL_POSITION_Y = 200;


class Game
{
public:
    Game(unsigned int pScreenWidth, unsigned int pScreenHeight, float pLogicalScreenWidth,
                float charAncho, float charAlto, Stage* stage, string OponentSide, int z_index);
    ~Game();
    void GameLoop();

private:

    MKCharacter* scorpion;
    Stage* stage;
    int ScreenWidth;
    int ScreenHeight;
    float logicalScreenWidth;
    GameView* gameView;
    GameController* gameController;
    CameraController* cameraController;
    string oponentSide;

};

#endif // GAME_H
