#ifndef MORTALKOMBAT_TALLER1C2015_HIGHKICKHITTING_H
#define MORTALKOMBAT_TALLER1C2015_HIGHKICKHITTING_H

#include "Character.h"

class HighKickHitting : public CharacterState {

public:
    HighKickHitting();
    ~HighKickHitting();
    void update(Character* character, Events aEvent );

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_HIGHKICKHITTING_H
