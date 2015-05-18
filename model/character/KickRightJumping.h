#ifndef MORTALKOMBAT_TALLER1C2015_KICKRIGHTJUMPING_H
#define MORTALKOMBAT_TALLER1C2015_KICKRIGHTJUMPING_H


#include "CharacterState.h"

class KickRightJumping : CharacterState {

public:
    KickRightJumping();
    ~KickRightJumping();
    void update(MKCharacter* character, Events aEvent);
    
    string getName();
    float getWidth();

};


#endif //MORTALKOMBAT_TALLER1C2015_KICKRIGHTJUMPING_H
