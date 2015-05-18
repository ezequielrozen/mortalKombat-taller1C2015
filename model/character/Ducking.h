//
// Created by mauri on 17/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_DUCKING_H
#define MORTALKOMBAT_TALLER1C2015_DUCKING_H


#include "CharacterState.h"

class Ducking : public CharacterState {

public:
    Ducking();
    ~Ducking();
    void update(MKCharacter * character, Events aEvent );

    string getName();
    float getWidth();

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_DUCKING_H
