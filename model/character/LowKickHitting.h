#ifndef MORTALKOMBAT_TALLER1C2015_LOWKICKHITTING_H
#define MORTALKOMBAT_TALLER1C2015_LOWKICKHITTING_H


#include "Character.h"

class LowKickHitting : public CharacterState {

public:
    LowKickHitting();
    ~LowKickHitting();
    void update(Character* character, Events aEvent );

private:
    int timer;

};


#endif //MORTALKOMBAT_TALLER1C2015_LOWKICKHITTING_H
