#include "CharacterState.h"

#ifndef MORTALKOMBAT_TALLER1C2015_RECEIVINGDUCKPUNCH_H
#define MORTALKOMBAT_TALLER1C2015_RECEIVINGDUCKPUNCH_H


class ReceivingDuckingPunch : public CharacterState {

public:
    ReceivingDuckingPunch();
    ~ReceivingDuckingPunch();
    void update(MKCharacter* character, Events aEvent);
    string getName();
    float getJumpLevel();
    float getWidth();

    bool isJumping();
};


#endif //MORTALKOMBAT_TALLER1C2015_RECEIVINGDUCKPUNCH_H