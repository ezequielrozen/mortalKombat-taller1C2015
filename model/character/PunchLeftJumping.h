#ifndef MORTALKOMBAT_TALLER1C2015_PUNCHLEFTJUMPING_H
#define MORTALKOMBAT_TALLER1C2015_PUNCHLEFTJUMPING_H


#include "CharacterState.h"

class PunchLeftJumping : CharacterState {

public:
    PunchLeftJumping();
    ~PunchLeftJumping();
    void update(MKCharacter* character, Events event);
    float getWidth();
};


#endif //MORTALKOMBAT_TALLER1C2015_PUNCHLEFTJUMPING_H
