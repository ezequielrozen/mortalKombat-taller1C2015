#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>

using namespace std;

class GameController
{
public:
    GameController();
    ~GameController(void);
    string getCommand();

    SDL_Event* getEvent();

    void checkEvent();


private:

    int timeCheck;

    string command;

    SDL_Event* mainEvent;


};

#endif /* GAMECONTROLLER_H_ */