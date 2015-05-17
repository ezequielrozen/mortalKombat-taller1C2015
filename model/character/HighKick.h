#ifndef MORTALKOMBAT_TALLER1C2015_HIGHKICK_H
#define MORTALKOMBAT_TALLER1C2015_HIGHKICK_H

#include "Character.h"

class HighKick : public CharacterState {

public:
    HighKick();
    ~HighKick();
    void update(Character* character, Events aEvent );

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_HIGHKICK_H
