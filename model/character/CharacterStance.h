#ifndef MORTALKOMBAT_TALLER1C2015_CHARACTERSTANCE_H
#define MORTALKOMBAT_TALLER1C2015_CHARACTERSTANCE_H

#include "Character.h"

class CharacterStance : public CharacterState {

public:
    CharacterStance();
    ~CharacterStance();

    void update(Character* character, MKEvent* aEvent);
    void getState();
};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTERSTANCE_H
