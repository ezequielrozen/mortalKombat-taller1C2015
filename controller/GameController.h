#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "../model/GameSetup.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>

using namespace std;

class GameController
{
public:
    GameController(GameSetup* pGameSetup);
    ~GameController(void);
    string getCommand();


private:

    GameSetup* gameSetup;

    int timeCheck;

    string command;


};

#endif /* GAMECONTROLLER_H_ */