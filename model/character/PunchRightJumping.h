#ifndef MORTALKOMBAT_TALLER1C2015_PUNCHRIGHTJUMPING_H
#define MORTALKOMBAT_TALLER1C2015_PUNCHRIGHTJUMPING_H


#include "CharacterState.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"

class PunchRightJumping : public CharacterState {

public:
    PunchRightJumping();
    ~PunchRightJumping();
    void update(MKCharacter* character, Events aEvent);
    
    string getName();
    float getWidth();
    bool isJumping();
    bool isMovingRight();
    bool isHitting();
    bool impact();
    void disableImpact(MKCharacter* character);
};


#endif //MORTALKOMBAT_TALLER1C2015_PUNCHRIGHTJUMPING_H
