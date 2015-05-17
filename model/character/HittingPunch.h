#ifndef MORTALKOMBAT_TALLER1C2015_HITTINGPUNCH_H
#define MORTALKOMBAT_TALLER1C2015_HITTINGPUNCH_H

#include "CharacterState.h"

class HittingPunch : public CharacterState {

public:
    HittingPunch();
    ~HittingPunch();
    void update(MKCharacter * character, Events aEvent );

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_HITTINGPUNCH_H
