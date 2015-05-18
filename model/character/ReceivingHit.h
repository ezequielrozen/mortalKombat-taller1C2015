#ifndef MORTALKOMBAT_TALLER1C2015_RECEIVINGHIT_H
#define MORTALKOMBAT_TALLER1C2015_RECEIVINGHIT_H


#include "../MKCharacter.h"

class ReceivingHit :public CharacterState {

public:
    ReceivingHit();
    ~ReceivingHit();
    void update(MKCharacter* character, Events aEvent);

    string getName();
    float getWidth();
};


#endif //MORTALKOMBAT_TALLER1C2015_RECEIVINGHIT_H
