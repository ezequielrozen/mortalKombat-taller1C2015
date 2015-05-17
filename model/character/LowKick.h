#ifndef MORTALKOMBAT_TALLER1C2015_LOWKICK_H
#define MORTALKOMBAT_TALLER1C2015_LOWKICK_H


#include "Character.h"

class LowKick : public CharacterState {

public:
    LowKick();
    ~LowKick();
    void update(Character* character, Events aEvent );

private:
    int timer;

};


#endif //MORTALKOMBAT_TALLER1C2015_LOWKICK_H
