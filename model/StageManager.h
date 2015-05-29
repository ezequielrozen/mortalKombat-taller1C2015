#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include "constantes.h"
#include "../controller/InputController.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GameLoader.h"
#include "Game.h"
#include "ModeSelection.h"
#include "CharacterSelection.h"
#include <iostream>
#include <SDL2/SDL_mixer.h>

using namespace std;

class StageManager
{
public:
    StageManager(char* filePath);
    ~StageManager();
    bool mainLoop();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    Game* game;
    GameLoader* gameLoader;
    ModeSelection* modeSelection;
    CharacterSelection* characterSelection;
};

#endif // STAGEMANAGER_H
