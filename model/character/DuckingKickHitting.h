#ifndef MORTALKOMBAT_TALLER1C2015_DUCKINGKICKHITTING_H
#define MORTALKOMBAT_TALLER1C2015_DUCKINGKICKHITTING_H


#include "CharacterState.h"

class DuckingKickHitting : public CharacterState {

public:
    DuckingKickHitting();
    ~DuckingKickHitting();
    void update(MKCharacter* character, Events aEvent);
    float getWidth();

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_DUCKINGKICKHITTING_H
