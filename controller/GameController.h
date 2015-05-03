#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "SDL2/SDL.h"
#include "../model/constantes.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>
#include <bits/stl_list.h>
#include "../model/MKCharacter.h"
#include "../model/stage/Layer.h"

using namespace std;

class GameController
{
public:
    GameController();
    ~GameController(void);

    void update(MKCharacter* character, MKCharacter* character2);

    SDL_Event* getEvent();

    void checkEvent();


private:

    int timer;

    SDL_Event* mainEvent;


};

#endif /* GAMECONTROLLER_H_ */