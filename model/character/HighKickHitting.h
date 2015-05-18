#ifndef MORTALKOMBAT_TALLER1C2015_HIGHKICKHITTING_H
#define MORTALKOMBAT_TALLER1C2015_HIGHKICKHITTING_H

#include "../MKCharacter.h"

class HighKickHitting : public CharacterState {

public:
    HighKickHitting();
    ~HighKickHitting();
    void update(MKCharacter* character, Events aEvent );
    
    string getName();
    float getWidth();

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_HIGHKICKHITTING_H
