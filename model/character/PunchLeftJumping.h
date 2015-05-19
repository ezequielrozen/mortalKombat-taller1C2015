#ifndef MORTALKOMBAT_TALLER1C2015_PUNCHLEFTJUMPING_H
#define MORTALKOMBAT_TALLER1C2015_PUNCHLEFTJUMPING_H


#include "CharacterState.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"

class PunchLeftJumping : public CharacterState {

public:
    PunchLeftJumping();
    ~PunchLeftJumping();
    void update(MKCharacter* character, Events aEvent);
    
    string getName();
    float getWidth();
    bool isJumping();
    bool isMovingLeft();
    bool isHitting();
};


#endif //MORTALKOMBAT_TALLER1C2015_PUNCHLEFTJUMPING_H
