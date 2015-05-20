#ifndef GAME_H
#define GAME_H

#include "MKCharacter.h"
#include "constantes.h"
#include "../view/GameView.h"
//#include "../controller/GameController.h" //TODO: ESTO CUANDO SE PASE A INPUT CONTROLLER HAY Q BORRARLO
#include "../controller/InputController.h"
#include "../controller/CameraController.h"
#include "../controller/Collider.h"
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
    bool GameLoop();
    void initGame(char*);

private:
    void updateGameState();
    MKCharacter* scorpion;
    MKCharacter* raiden;
    Stage* stage;
    int ScreenWidth;
    int ScreenHeight;
    GameView* gameView;
//    GameController* gameController;//TODO: ESTO CUANDO SE PASE A INPUT CONTROLLER HAY Q BORRARLO
    InputController* inputController;
    CameraController* cameraController;
    Collider* collider;
    string oponentSide;

    GameLoader *gameLoader;


    int peviousKey;
};

#endif // GAME_H
