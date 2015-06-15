//
// Created by her on 14/06/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_RECEIVINGICE_H
#define MORTALKOMBAT_TALLER1C2015_RECEIVINGICE_H


#include "CharacterState.h"

class ReceivingIce : public CharacterState {
public:
    ReceivingIce();
    virtual ~ReceivingIce();
    string getName();
    //float getWidth();
    void refreshTimer(MKCharacter* character);
    void update(MKCharacter * character, Events aEvent);
private:
    int timer;
};

#endif //MORTALKOMBAT_TALLER1C2015_RECEIVINGICE_H
