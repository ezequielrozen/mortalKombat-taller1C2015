#ifndef MORTALKOMBAT_TALLER1C2015_RECEIVINGHIGHPUNCH_H
#define MORTALKOMBAT_TALLER1C2015_RECEIVINGHIGHPUNCH_H


#include "../MKCharacter.h"

class ReceivingHighPunch :public CharacterState {

public:
    ReceivingHighPunch();
    ~ReceivingHighPunch();
    void update(MKCharacter* character, Events aEvent);

    string getName();
    float getWidth();
};


#endif //MORTALKOMBAT_TALLER1C2015_RECEIVINGHIGHPUNCH_H
