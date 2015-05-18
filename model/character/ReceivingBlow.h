#ifndef MORTALKOMBAT_TALLER1C2015_RECEIVINGBLOW_H
#define MORTALKOMBAT_TALLER1C2015_RECEIVINGBLOW_H


#include "../MKCharacter.h"

class ReceivingBlow : CharacterState {

public:
    ReceivingBlow();
    ~ReceivingBlow();
    void update(MKCharacter* character, Events aEvent);

    string getName();
    float getWidth();

};


#endif //MORTALKOMBAT_TALLER1C2015_RECEIVINGBLOW_H
