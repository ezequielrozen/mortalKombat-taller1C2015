#ifndef MORTALKOMBAT_TALLER1C2015_RECEIVINGHIGHPUNCH_H
#define MORTALKOMBAT_TALLER1C2015_RECEIVINGHIGHPUNCH_H


#include "../MKCharacter.h"

class ReceivingHighPunch : CharacterState {

public:
    ReceivingHighPunch();
    ~ReceivingHighPunch();
    void update(MKCharacter* character, Events aEvent);
};


#endif //MORTALKOMBAT_TALLER1C2015_RECEIVINGHIGHPUNCH_H
