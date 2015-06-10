#ifndef GAME_H
#define GAME_H

#include "MKCharacter.h"
#include "constantes.h"
#include "../view/GameView.h"
#include "../controller/InputController.h"
#include "../controller/CameraController.h"
#include "../controller/Collider.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "stage/Stage.h"
#include "GameLoader.h"
#include "character/ComboManager.h"
#include "util/Timer.h"
#include <math.h>
#include <iostream>
#include <SDL2/SDL_mixer.h>

using namespace std;

class Game
{
public:
    Game(GameLoader* aGameLoader, SDL_Renderer* renderer, InputController* inputController);
    ~Game();
    bool GameLoop(GameModes mode);
    void initGame(SDL_Renderer* renderer, InputController* stageController);

private:
    void updateGameState(int &roundCount);
    MKCharacter* scorpion;
    MKCharacter* raiden;
    Stage* stage;
    int ScreenWidth;
    int ScreenHeight;
    GameView* gameView;
    InputController* inputController;
    CameraController* cameraController;
    Collider* collider;
    string oponentSide;
    GameLoader *gameLoader;
    int diedTimeElapsed;
    int timeToResetRound;
    int timeFightStart;

    ComboManager* comboManager;
    int peviousKey;
    bool isRoundEnd;

    void restartRound();
    bool endFightTime();
    bool endOfRound();
    Timer* timer;
};

#endif // GAME_H
