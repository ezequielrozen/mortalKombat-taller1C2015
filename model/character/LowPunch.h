#ifndef MORTALKOMBAT_TALLER1C2015_LOWPUNCH_H
#define MORTALKOMBAT_TALLER1C2015_LOWPUNCH_H

#include "CharacterState.h"

class LowPunch : public CharacterState {

public:
    LowPunch();
    ~LowPunch();
    void update(Character* character, Events aEvent );

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_LOWPUNCH_H
