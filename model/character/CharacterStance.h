#ifndef MORTALKOMBAT_TALLER1C2015_CHARACTERSTANCE_H
#define MORTALKOMBAT_TALLER1C2015_CHARACTERSTANCE_H

#include "Character.h"

class CharacterStance : public CharacterState {

public:
    CharacterStance();
    ~CharacterStance();

    void update(Character* character, Events aEvent);
    void getState();

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_CHARACTERSTANCE_H
