#ifndef MORTALKOMBAT_TALLER1C2015_CHARACTERSTANCE_H
#define MORTALKOMBAT_TALLER1C2015_CHARACTERSTANCE_H

#include "../MKCharacter.h"

class CharacterStance : public CharacterState {

public:
    CharacterStance();
    ~CharacterStance();

    void update(MKCharacter * character, Events aEvent);

    string getName();

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTERSTANCE_H
