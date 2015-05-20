//
// Created by mauri on 17/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_VICTORY_H
#define MORTALKOMBAT_TALLER1C2015_VICTORY_H


#include "CharacterState.h"

class Victory : public CharacterState {

public:
    Victory();
    ~Victory();
    void update(MKCharacter * character, Events aEvent );
    string getName();

};


#endif //MORTALKOMBAT_TALLER1C2015_VICTORY_H
