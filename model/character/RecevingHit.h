#ifndef MORTALKOMBAT_TALLER1C2015_RECEVINGHIT_H
#define MORTALKOMBAT_TALLER1C2015_RECEVINGHIT_H

#include "../MKCharacter.h"

class RecevingHit : public CharacterState {

public:
    RecevingHit();
    ~RecevingHit();
    void update(MKCharacter* character, Events aEvent );

    string getName();
    float getWidth();
    void refreshTimer(MKCharacter* character);
    
private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_RECEVINGHIT_H
