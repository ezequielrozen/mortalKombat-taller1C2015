#ifndef GAME_H
#define GAME_H

#include "MKCharacter.h"
#include "constantes.h"
#include "../view/GameView.h"
#include "../controller/GameController.h"
#include "../controller/CameraController.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "stage/Stage.h"
#include "GameLoader.h"
#include <math.h>
#include <iostream>

using namespace std;

class Game
{
public:
    Game(GameLoader* aGameLoader, char* filePath);
    ~Game();
    void GameLoop();
    void initGame(char*);

private:

    MKCharacter* scorpion;
    Stage* stage;
    int ScreenWidth;
    int ScreenHeight;
    GameView* gameView;
    GameController* gameController;
    CameraController* cameraController;
    string oponentSide;

    GameLoader *gameLoader;
};

#endif // GAME_H
