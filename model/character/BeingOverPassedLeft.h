//
// Created by mauri on 24/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_BEINGOVERPASSEDLEFT_H
#define MORTALKOMBAT_TALLER1C2015_BEINGOVERPASSEDLEFT_H


#include "../MKCharacter.h"

class BeingOverPassedLeft : public CharacterState {
public:

    BeingOverPassedLeft();
    virtual ~BeingOverPassedLeft();

    void update(MKCharacter *character, Events aEvent);

    bool isMovingLeft();
    bool isBeingOverPassedLeft();

    string getName();
};


#endif //MORTALKOMBAT_TALLER1C2015_BEINGOVERPASSEDLEFT_H
