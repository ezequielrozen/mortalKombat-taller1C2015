#ifndef MORTALKOMBAT_TALLER1C2015_DEAD_H
#define MORTALKOMBAT_TALLER1C2015_DEAD_H

#include "CharacterState.h"

class Dead : public CharacterState {

public:
    Dead();
    ~Dead();

private:
    void update(MKCharacter* character, Events aEvent);
    string getName();
    float getWidth();
};


#endif //MORTALKOMBAT_TALLER1C2015_DEAD_H
