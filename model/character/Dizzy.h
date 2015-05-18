#ifndef MORTALKOMBAT_TALLER1C2015_DIZZY_H
#define MORTALKOMBAT_TALLER1C2015_DIZZY_H

#include "CharacterState.h"

class Dizzy : public CharacterState {

public:
    Dizzy();
    ~Dizzy();
    void update(MKCharacter* character, Events aEvent);

    string getName();
    float getWidth();
};


#endif //MORTALKOMBAT_TALLER1C2015_DIZZY_H
