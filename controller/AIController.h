#ifndef MORTALKOMBAT_TALLER1C2015_AICONTROLLER_H
#define MORTALKOMBAT_TALLER1C2015_AICONTROLLER_H


#include "SDL2/SDL_events.h"
#include "../model/MKCharacter.h"
#include "MKStageController.h"

class AIController {

public:
    AIController(MKStageController* stageController);
    ~AIController();
    void update(MKCharacter* character1, MKCharacter* character2, SDL_Event* mainEvent);

    MKStageController *stageController;
    bool key_u_Released;
};


#endif //MORTALKOMBAT_TALLER1C2015_AICONTROLLER_H
