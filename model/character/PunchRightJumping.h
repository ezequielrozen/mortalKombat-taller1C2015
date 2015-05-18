#ifndef MORTALKOMBAT_TALLER1C2015_PUNCHRIGHTJUMPING_H
#define MORTALKOMBAT_TALLER1C2015_PUNCHRIGHTJUMPING_H


#include "CharacterState.h"

class PunchRightJumping : CharacterState {

public:
    PunchRightJumping();
    ~PunchRightJumping();
    void update(MKCharacter* character, Events aEvent);
    float getWidth();
};


#endif //MORTALKOMBAT_TALLER1C2015_PUNCHRIGHTJUMPING_H
