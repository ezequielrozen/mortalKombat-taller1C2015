#ifndef MORTALKOMBAT_TALLER1C2015_HIGHPUNCHHITTING_H
#define MORTALKOMBAT_TALLER1C2015_HIGHPUNCHHITTING_H

#include "CharacterState.h"

class HighPunchHitting : public CharacterState {

public:
    HighPunchHitting();
    ~HighPunchHitting();
    void update(MKCharacter * character, Events aEvent );
    
    string getName();
    float getWidth();
    
private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_HIGHPUNCHHITTING_H
