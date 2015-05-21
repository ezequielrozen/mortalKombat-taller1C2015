#ifndef MORTALKOMBAT_TALLER1C2015_DUCKINGKICKHITTING_H
#define MORTALKOMBAT_TALLER1C2015_DUCKINGKICKHITTING_H


#include "CharacterState.h"

class DuckingKickHitting : public CharacterState {

public:
    DuckingKickHitting();
    ~DuckingKickHitting();
    void update(MKCharacter* character, Events aEvent);
    
    string getName();
    float getWidth();
    float getHeight();

    bool isDucking();
    bool isHitting();

    void refreshTimer(MKCharacter* character);
    bool impact();

private:
    int timer;
};


#endif //MORTALKOMBAT_TALLER1C2015_DUCKINGKICKHITTING_H
