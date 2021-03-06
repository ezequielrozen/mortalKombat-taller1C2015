#ifndef KEYBOARDCONTROLLER_H_
#define KEYBOARDCONTROLLER_H_

#include "SDL2/SDL.h"
#include "../model/constantes.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <iostream>
#include <bits/stl_list.h>
#include "../model/MKCharacter.h"
#include "../model/stage/Layer.h"
#include "EventController.h"

using namespace std;

class KeyboardController
{
public:
    KeyboardController(MKStageController* stageController);

    ~KeyboardController(void);

    void update(MKCharacter* character, MKCharacter* character2, SDL_Event* mainEvent);

    void setStageController(MKStageController* stageController);

private:


//    int timer;
//    int timerChar2;
//    int hitTimer;
//    int hitTimerChar2;
//    int hitTimerRaidenShootCheck;
//    bool raidenShootTimeOutCompleted;
//    int hitTimerScorpionShootCheck;
//    bool scorpionShootTimeOutCompleted;

//    SDL_Keycode previousKey;
//    SDL_Keycode previousKeyChar2;

    bool keysPressed[32];

//	void testElapsedTime(MKCharacter* character, MKCharacter* character2);
    MKStageController* stageController;

};



#endif
