#ifndef MORTALKOMBAT_TALLER1C2015_KICKRIGHTJUMPINGHITTING_H
#define MORTALKOMBAT_TALLER1C2015_KICKRIGHTJUMPINGHITTING_H


#include "CharacterState.h"

class KickRightJumpingHitting : public CharacterState {

public:
    KickRightJumpingHitting();
    ~KickRightJumpingHitting();
    void update(MKCharacter* character, Events aEvent);
    
    string getName();
    float getWidth();
    bool isHitting();
    bool isJumping();
    bool isMovingRight();
    bool impact();
    void disableImpact(MKCharacter* character);

};


#endif //MORTALKOMBAT_TALLER1C2015_KICKRIGHTJUMPINGHITTING_H
