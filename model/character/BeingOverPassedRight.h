//
// Created by mauri on 24/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_BEINGOVERPASSEDRIGHT_H
#define MORTALKOMBAT_TALLER1C2015_BEINGOVERPASSEDRIGHT_H


#include "../MKCharacter.h"

class BeingOverPassedRight : public CharacterState {
public:

    BeingOverPassedRight();
    virtual ~BeingOverPassedRight();


    void update(MKCharacter *character, Events aEvent);

    bool isMovingRight();
    bool isBeingOverPassedRight();

    string getName();
};


#endif //MORTALKOMBAT_TALLER1C2015_BEINGOVERPASSEDRIGHT_H
