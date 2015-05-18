#ifndef MORTALKOMBAT_TALLER1C2015_KICKLEFTJUMPINGHITTING_H
#define MORTALKOMBAT_TALLER1C2015_KICKLEFTJUMPINGHITTING_H


#include "CharacterState.h"

class KickLeftJumpingHitting : CharacterState {

public:
    KickLeftJumpingHitting();
    ~KickLeftJumpingHitting();
    void update(MKCharacter* character, Events aEvent);
    
    string getName();
    float getWidth();
};


#endif //MORTALKOMBAT_TALLER1C2015_KICKLEFTJUMPINGHITTING_H
