#ifndef MORTALKOMBAT_TALLER1C2015_RECEVINGHIT_H
#define MORTALKOMBAT_TALLER1C2015_RECEVINGHIT_H

#include "../MKCharacter.h"

class RecevingHit : public CharacterState {

public:
    RecevingHit();
    ~RecevingHit();
    void update(MKCharacter* character, Events aEvent );
    
private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_RECEVINGHIT_H
