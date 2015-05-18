#ifndef MORTALKOMBAT_TALLER1C2015_KICKLEFTJUMPING_H
#define MORTALKOMBAT_TALLER1C2015_KICKLEFTJUMPING_H


#include "CharacterState.h"

class KickLeftJumping : CharacterState {

public:
    KickLeftJumping();
    ~KickLeftJumping();
    void update(MKCharacter* character, Events aEvent);
    
    string getName();
    float getWidth();
};


#endif //MORTALKOMBAT_TALLER1C2015_KICKLEFTJUMPING_H
