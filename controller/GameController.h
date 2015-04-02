#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>
#include "../model/MKCharacter.h"
#include "../model/stage/Layer.h"

using namespace std;

class GameController
{
public:
    GameController();
    ~GameController(void);

    void update(MKCharacter* character, Layer* layer);

    SDL_Event* getEvent();

    void checkEvent();


private:

    int timer;

    SDL_Event* mainEvent;


};

#endif /* GAMECONTROLLER_H_ */