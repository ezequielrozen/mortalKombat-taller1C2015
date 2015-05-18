#ifndef MORTALKOMBAT_TALLER1C2015_RECEIVINGBLOW_H
#define MORTALKOMBAT_TALLER1C2015_RECEIVINGBLOW_H


#include "../MKCharacter.h"

class ReceivingBlow : CharacterState {

public:
    ReceivingBlow();
    ~ReceivingBlow();
    void update(MKCharacter* character, Events aEvent);

};


#endif //MORTALKOMBAT_TALLER1C2015_RECEIVINGBLOW_H
